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
	
}


// Called every frame
void UGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGrabComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent, TArray<class UInputAction*> inputs)
{
	//PlayerInputComponent->BindAction(inputs[2], ETriggerEvent::Started, this, &UGrabComponent::GrabObject);
	//PlayerInputComponent->BindAction(inputs[2], ETriggerEvent::Completed, this, &UGrabComponent::ReleaseObject);
}

void UGrabComponent::GrabObject()
{
	// 1. SweepTrace�� �̿��� ���
	if (currentObject == nullptr)
	{
		FHitResult hitInfo;
		FVector originLoc = player->rightHand->GetComponentLocation();
		FCollisionObjectQueryParams objectParams;
		objectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel2);

		FCollisionQueryParams params;
		params.AddIgnoredActor(player);

		bool bChecked = GetWorld()->SweepSingleByObjectType(hitInfo, originLoc, originLoc, FQuat::Identity, objectParams, FCollisionShape::MakeSphere(30), params);

		if (bChecked)
		{
			currentObject = Cast<APickUpActor>(hitInfo.GetActor());
			//UE_LOG(LogTemp, Warning, TEXT("%s(%d) - Hit Actor: %s"), *FString(__FUNCTION__), __LINE__, *hitInfo.GetActor()->GetActorNameOrLabel());

			if (currentObject != nullptr)
			{
				currentObject->OnGrabbed(player->rightHand);

				// ������ ��Ʈ�ѷ��� ���� ȿ���� �ش�.
				// player->pc->PlayHapticEffect(grabHaptic, EControllerHand::Right);
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

