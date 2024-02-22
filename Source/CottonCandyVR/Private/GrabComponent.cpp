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
	// 1. SweepTrace를 이용한 방식
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

				// 오른손 컨트롤러에 진동 효과를 준다.
				// player->pc->PlayHapticEffect(grabHaptic, EControllerHand::Right);
			}
		}
	}
}

void UGrabComponent::ReleaseObject()
{
	// 현재 쥐고 있는 물체가 있는지 확인한다.
	if (currentObject != nullptr)
	{
		// 오른손 콘트롤러의 위치 변화량을 계산한다.
		FVector deltaDirection = currentLocation_rightCon - previousLocation_rightCon;

		currentObject->OnReleased(deltaDirection);
		currentObject = nullptr;
	}
}

