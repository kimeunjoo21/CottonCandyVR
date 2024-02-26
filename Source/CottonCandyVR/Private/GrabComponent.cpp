// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "VRPlayer_M.h"
#include "PickUpActor.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values for this component's properties
UGrabComponent::UGrabComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	player = GetOwner<AVRPlayer_M>();
}


// Called every frame
void UGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ������ ��Ʈ�ѷ��� ��ġ ��ȭ���� �����Ѵ�.
	previousLocation_rightCon = currentLocation_rightCon;
	currentLocation_rightCon = player->rightHand->GetComponentLocation();

	FVector deltaDirection = currentLocation_rightCon - previousLocation_rightCon;
	//UE_LOG(LogTemp, Warning, TEXT("delta length: %f"), deltaDirection.Length());
}

void UGrabComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* playerInputComponent, TArray<class UInputAction*> inputs)
{
	playerInputComponent->BindAction(inputs[2], ETriggerEvent::Started, this, &UGrabComponent::GrabObject);
	UE_LOG(LogTemp, Warning, TEXT("444444444"));
	playerInputComponent->BindAction(inputs[2], ETriggerEvent::Completed, this, &UGrabComponent::ReleaseObject);

	
}

void UGrabComponent::GrabObject()
{
	UE_LOG(LogTemp, Warning, TEXT("55555555"));
	// 1. SweepTrace�� �̿��� ���
	if (currentObject == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("66666666"));
		FHitResult hitInfo;
		FVector originLoc = player->rightHand->GetComponentLocation();
		FCollisionObjectQueryParams objectParams;
		objectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel2);

		FCollisionQueryParams params;
		params.AddIgnoredActor(player);

		bool bChecked = GetWorld()->SweepSingleByObjectType(hitInfo, originLoc, originLoc, FQuat::Identity, objectParams, FCollisionShape::MakeSphere(200), params);
		//UE_LOG(LogTemp, Warning, TEXT("%s(%d) - Hit Actor: %s"), *FString(__FUNCTION__), __LINE__, *hitInfo.GetActor()->GetActorNameOrLabel());
		//UE_LOG(LogTemp, Warning, TEXT("1111111111111111111"));
		if (bChecked)
		{
		//UE_LOG(LogTemp, Warning, TEXT("%s(%d) - Hit Actor: %s"), *FString(__FUNCTION__), __LINE__, *hitInfo.GetActor()->GetActorNameOrLabel());
		//UE_LOG(LogTemp, Warning, TEXT("22222222222221222"));
		currentObject = Cast<APickUpActor>(hitInfo.GetActor());
		UE_LOG(LogTemp, Warning, TEXT("7777777"));

			if (currentObject != nullptr)
			{
				currentObject->OnGrabbed(player->rightHand);
				UE_LOG(LogTemp, Warning, TEXT("8888888"));
				// ������ ��Ʈ�ѷ��� ���� ȿ���� �ش�.
				//player->pc->PlayHapticEffect(grabHaptic, EControllerHand::Right);
			}
		}
	}
}

void UGrabComponent::ReleaseObject()
{
	// ���� ��� �ִ� ��ü�� �ִ��� Ȯ���Ѵ�.
	if (currentObject != nullptr)
	{
		// ������ ��Ʈ�ѷ��� ��ġ ��ȭ���� ����Ѵ�.
		FVector deltaDirection = currentLocation_rightCon - previousLocation_rightCon;

		currentObject->OnReleased(deltaDirection);
		currentObject = nullptr;
	}
}

