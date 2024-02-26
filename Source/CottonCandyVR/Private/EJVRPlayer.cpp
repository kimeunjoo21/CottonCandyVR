// Fill out your copyright notice in the Description page of Project Settings.


#include "EJVRPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "Components/TextRenderComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "EJGrabComponent.h"


// Sets default values
AEJVRPlayer::AEJVRPlayer()
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
	leftHand->SetRelativeRotation(FRotator(0, 180, -270));


	rightMotion = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Motion Controller"));
	rightMotion->SetupAttachment(RootComponent);
	rightMotion->MotionSource = FName("Right");

	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand Mesh"));
	rightHand->SetupAttachment(rightMotion);
	rightHand->SetRelativeRotation(FRotator(0, 0, 90));


	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	grabComp = CreateDefaultSubobject<UEJGrabComponent>(TEXT("GrabComponent"));

}

// Called when the game starts or when spawned
void AEJVRPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* pc = GetController<APlayerController>();
	if (pc != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());

		if (subsys != nullptr)
		{
			subsys->AddMappingContext(vrMapping, 0);
		}
	}

	// HMD 장비의 기준점 설정
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Type::Eye);

}

// Called every frame
void AEJVRPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEJVRPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (enhancedInputComponent != nullptr)
	{
		enhancedInputComponent->BindAction(vrInputs[2], ETriggerEvent::Triggered, this, &AEJVRPlayer::Move);
		enhancedInputComponent->BindAction(vrInputs[2], ETriggerEvent::Completed, this, &AEJVRPlayer::Move);
		enhancedInputComponent->BindAction(vrInputs[3], ETriggerEvent::Triggered, this, &AEJVRPlayer::Rotate);
		enhancedInputComponent->BindAction(vrInputs[3], ETriggerEvent::Completed, this, &AEJVRPlayer::Rotate);

		grabComp->SetupPlayerInputComponent(enhancedInputComponent, vrInputs);

	}


}

void AEJVRPlayer::Move(const FInputActionValue& val)
{
	FVector2D dir = val.Get<FVector2D>();

	// 현재 바라보고 있는 방향으로 이동한다.
	FVector originVec = FVector(dir.Y, dir.X, 0);
	FVector newVec = GetTransform().TransformVector(originVec);

	AddMovementInput(newVec);

}

void AEJVRPlayer::Rotate(const FInputActionValue& val)
{

	FVector2D dir = val.Get<FVector2D>();

	// 입력받은 방향으로 회전한다.
	AddControllerYawInput(dir.X);

}

