// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPlayer_M.h"
#include <Camera/CameraComponent.h>
#include <Components/StaticMeshComponent.h>
#include <MotionControllerComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


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
	//leftHand->SetRelativeRotation(FRotator(0,0,0));

	rightMotion = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Motion Controller"));
	rightMotion->SetupAttachment(rightMotion);
	rightMotion->MotionSource = FName("Right");

	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand Mesh"));
	rightHand->SetupAttachment(rightMotion);
	// rightHand->SetRelativeRotation(FRotator(90, 0, 90));
	// (Pitch = 90.000000, Yaw = 0.000000, Roll = 90.000000)

	

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
}

// Called every frame
void AVRPlayer_M::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRPlayer_M::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	UE_LOG(LogTemp, Warning, TEXT("1111111111111111111"));
	if (enhancedInputComponent != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("2222222222222"));
		// ia_rightThumbStickAxis : 오른손 컨트롤러 조이스틱을 통한 회전(틱 느낌으로 회전하는게 나을지?) (마우스로 회전 가능)
		enhancedInputComponent->BindAction(vrInputs[0], ETriggerEvent::Triggered, this, &AVRPlayer_M::Rotate);
		enhancedInputComponent->BindAction(vrInputs[0], ETriggerEvent::Completed, this, &AVRPlayer_M::Rotate);
		UE_LOG(LogTemp, Warning, TEXT("333333333333333333"));
		// ia_leftThumbStickAxis : 왼손 컨트롤러의 조이스틱을 통한 움직임 (키보드 WASD)
		enhancedInputComponent->BindAction(vrInputs[1], ETriggerEvent::Triggered, this, &AVRPlayer_M::Move);
		enhancedInputComponent->BindAction(vrInputs[1], ETriggerEvent::Completed, this, &AVRPlayer_M::Move);
		UE_LOG(LogTemp, Warning, TEXT("444444444444"));
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

