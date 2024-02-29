// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPlayer_M.h"
#include <Camera/CameraComponent.h>
#include <Components/StaticMeshComponent.h>
#include <MotionControllerComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <HeadMountedDisplayFunctionLibrary.h>
#include "GrabComponent.h"
#include "InputAction.h"
//박스컴포넌트
#include<Components/BoxComponent.h>
#include "UILineActor.h"
#include "NiagaraComponent.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"
#include "Components/WidgetInteractionComponent.h"

// UE_LOG(LogTemp, Warning, TEXT("1111111111111111111"));
// Sets default values
AVRPlayer_M::AVRPlayer_M()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	cameraComp->SetupAttachment(RootComponent);

	headMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadMesh"));
	headMesh->SetupAttachment(cameraComp);

	leftMotion = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Motion Controller"));
	leftMotion->SetupAttachment(RootComponent);
	leftMotion->MotionSource = FName("Left");

	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand Mesh"));
	leftHand->SetupAttachment(leftMotion);
	leftHand->SetRelativeRotation(FRotator(-90,0,-90));
	// (Pitch=-90.000000,Yaw=0.000000,Roll=-90.000000)
	rightMotion = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Motion Controller"));
	rightMotion->SetupAttachment(RootComponent);
	rightMotion->MotionSource = FName("Right");

	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand Mesh"));
	rightHand->SetupAttachment(rightMotion);
	rightHand->SetRelativeRotation(FRotator(90, 0, 90));
	// (Pitch = 90.000000, Yaw = 0.000000, Roll = 90.000000)


	grabComp = CreateDefaultSubobject<UGrabComponent>(TEXT("Grab Component"));

	lineFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Line Effect"));
	lineFX->SetupAttachment(leftMotion);
	lineFX->SetVisibility(false);


}

// Called when the game starts or when spawned
void AVRPlayer_M::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* pc = GetController<APlayerController>();
	if (pc != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
		(GetController<APlayerController>()->GetLocalPlayer());

		if (subsys != nullptr)
		{
			subsys->AddMappingContext(vrMapping, 0); // 뒤에 0 값?
		}
	}

	// HMD 장비의 기준점 설정
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Type::Eye);

	// RingActor 코드 가져온 것
	/*lineInstance = GetWorld()->SpawnActor<AUILineActor>(lineActor,this->GetActorLocation(), this->GetActorRotation());
	lineInstance->lineFX->SetVisibility(false);*/


}

// Called every frame
void AVRPlayer_M::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsShowLine && this != nullptr)
	{
		UMotionControllerComponent* leftMotionCon = this->leftMotion;
		if (leftMotionCon != nullptr)
		{	
			FVector handLocation = leftMotionCon->GetComponentLocation();
			FVector direction = leftMotionCon->GetForwardVector();

			// 베지어 곡선 방식으로 그린다.
			// DrawBezierLine(rightMotionCon);

			DrawLineTrajectory(handLocation, direction, power, throwTime, throwTerm);
		}
	}

}

// Called to bind functionality to input
void AVRPlayer_M::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	if (enhancedInputComponent != nullptr)
	{
		grabComp->SetupPlayerInputComponent(enhancedInputComponent, vrInputs);
		
		// ia_rightThumbStickAxis : 오른손 컨트롤러 조이스틱을 통한 회전(틱 느낌으로 회전하는게 나을지?) (마우스로 회전 가능)
		enhancedInputComponent->BindAction(vrInputs[0], ETriggerEvent::Triggered, this, &AVRPlayer_M::Rotate);
		enhancedInputComponent->BindAction(vrInputs[0], ETriggerEvent::Completed, this, &AVRPlayer_M::Rotate);
		
		// ia_leftThumbStickAxis : 왼손 컨트롤러의 조이스틱을 통한 움직임 (키보드 WASD)
		enhancedInputComponent->BindAction(vrInputs[1], ETriggerEvent::Triggered, this, &AVRPlayer_M::Move);
		enhancedInputComponent->BindAction(vrInputs[1], ETriggerEvent::Completed, this, &AVRPlayer_M::Move);

		//enhancedInputComponent->BindAction(vrInputs[2], ETriggerEvent::Started, this, &UGrabComponent::GrabObject);

		//enhancedInputComponent->BindAction(vrInputs[2], ETriggerEvent::Started, this, &UGrabComponent::GrabObject);
		//enhancedInputComponent->BindAction(vrInputs[2], ETriggerEvent::Completed, this, &UGrabComponent::ReleaseObject);
	
		enhancedInputComponent->BindAction(vrInputs[3], ETriggerEvent::Started, this, &AVRPlayer_M::ShowUILine);
		//enhancedInputComponent->BindAction(vrInputs[3], ETriggerEvent::Completed, this, &AVRPlayer_M::UnShowUILine);

		enhancedInputComponent->BindAction(vrInputs[4], ETriggerEvent::Triggered, this, &AVRPlayer_M::ShowMenuUI);

		
	}
}

void AVRPlayer_M::Move(const FInputActionValue& val)
{
	FVector2D dir = val.Get<FVector2D>();

	// 현재 바라보고 있는 방향으로 이동한다.
	FVector originVec = FVector(dir.Y, dir.X, 0);
	FVector newVec = GetTransform().TransformVector(originVec);

	AddMovementInput(newVec);
	//AddMovementInput(FVector(dir.Y, dir.X, 0));

}

void AVRPlayer_M::Rotate(const FInputActionValue& val)
{
	FVector2D dir = val.Get<FVector2D>();

	// 입력받은 방향으로 회전한다.
	AddControllerYawInput(dir.X);
}

void AVRPlayer_M::UIInteraction(const FInputActionValue& val)
{
	// DrawLineTrajectory();
}

void AVRPlayer_M::ShowUILine()
{
	if(bIsShowLine == false)
	{
		bIsShowLine = true;
		UE_LOG(LogTemp, Warning, TEXT("0001111"));

		/*if (bIsShowLine == true &&)
		{
		}*/
	}

	else if (bIsShowLine == true)
	{
		bIsShowLine = false;
		lineFX->SetVisibility(false);
	}

	

}

void AVRPlayer_M::DrawLineTrajectory(FVector startLoc, FVector dir, float throwPower, float time, int32 term)
{

	float interval = time / (float)term;
	throwPoints.Empty();
	throwPoints.Add(startLoc);
	UE_LOG(LogTemp, Warning, TEXT("0002222"));

	for (int32 i = 0; i < term; i++)
	{
		// p = p0 + vt - 0.5 * g * m * m * t * t
		float t = interval * i;
		// float mass = ballInstance->sphereComp->GetMass();
		// float gravity = 0.5f * GetWorld()->GetDefaultGravityZ() * mass * mass * t * t;
		// FVector curLocation = startLoc + dir * throwPower * t +FVector(0, 0, gravity);
		FVector curLocation = startLoc + dir * throwPower * t ;

		// 각 구간마다의 충돌 여부를 체크
		FHitResult hitInfo;
		FVector startVec = throwPoints[throwPoints.Num() - 1];
		UE_LOG(LogTemp, Warning, TEXT("0003333"));
		if (GetWorld()->LineTraceSingleByChannel(hitInfo, startVec, curLocation, ECC_Visibility))
		{
			throwPoints.Add(hitInfo.ImpactPoint);
			UE_LOG(LogTemp, Warning, TEXT("0004444"));
			break;
		}
		
		throwPoints.Add(curLocation);
		UE_LOG(LogTemp, Warning, TEXT("0005555"));
	}


	if (throwPoints.Num() > 1)
	{
		for (int32 i = 0; i < throwPoints.Num() - 1; i++)
		{
			//DebugLine을 이용해서 그리기
			//DrawDebugLine(GetWorld(), throwPoints[i], throwPoints[i + 1], FColor::Red, false, 0, 0, 2);

			// NiagaraSystem을 이용해서 그리기
			lineFX->SetVisibility(true);
			UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(this->lineFX, FName("PointArray"), throwPoints);
			UE_LOG(LogTemp, Warning, TEXT("0000000000"));
			//lineInstance->lineFX->SetVisibility(true);
			//lineInstance->SetActorLocation(throwPoints[throwPoints.Num() - 1]);
			
			
			// lineInstance->SetActorLocation(throwPoints[throwPoints.Num() - 1]);
		
		}
	}


}

void AVRPlayer_M::UnShowUILine()
{
	bIsShowLine = false;
	lineFX->SetVisibility(false);

	/*TArray<FVector> initVector;
	initVector.SetNum(2);*/
}

void AVRPlayer_M::ShowMenuUI()
{
	if (bIsShowMenuUI == false)
	{
		bIsShowMenuUI = true;
		UE_LOG(LogTemp, Warning, TEXT("trueMenu"));
	}
	else if(bIsShowMenuUI == true)
	{
		bIsShowMenuUI = false;
		UE_LOG(LogTemp, Warning, TEXT("falseMenu"));
	}
}


void AVRPlayer_M::ClickLeftMouseButtonPress()
{
	// 키보드 버튼을 누른 효과를 줄 때
	// widgetPointerRight->PressKey(EKeys::Y);

	// 마우스 버튼을 누른 효과를 줄 때
	//widgetPointerRight->PressPointerKey(EKeys::LeftMouseButton);
}

void AVRPlayer_M::ClickLeftMouseButtonRelease()
{
	// widgetPointerRight->ReleasePointerKey(EKeys::LeftMouseButton);
}


