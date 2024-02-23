// Fill out your copyright notice in the Description page of Project Settings.


#include "EJGrabComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EJVRPlayer.h"
#include "SugarSpoon.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values for this component's properties
UEJGrabComponent::UEJGrabComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEJGrabComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	player = GetOwner<AEJVRPlayer>();
}


// Called every frame
void UEJGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...


	//오른손 컨트롤러의 위치 변화값을 저장한다.
	previousLocation_rightCon = currentLocation_rightCon;
	currentLocation_rightCon = player->rightHand->GetComponentLocation();

	//FVector deltaDirection = currentLocation_rightCon - previousLocation_rightCon;
	//UE_LOG(LogTemp, Warning, TEXT("delta length: %f"), deltaDirection.Length());

	//오른손 콘트롤러의 회전값을 저장한다
	previousRotation_rightCon = currentRotation_rightCon;
	currentRotation_rightCon = player->rightHand->GetComponentQuat();

}

void UEJGrabComponent::SetupPlayerInputComponent(UEnhancedInputComponent* PlayerInputComponent, TArray<class UInputAction*> inputs)
{
	PlayerInputComponent->BindAction(inputs[0], ETriggerEvent::Started, this, &UEJGrabComponent::GrabObject);
	PlayerInputComponent->BindAction(inputs[0], ETriggerEvent::Completed, this, &UEJGrabComponent::ReleaseObject);

}

void UEJGrabComponent::GrabObject()
{
	if (currentObj == nullptr) {
		// 1. SweepTrace를 이용한 방식
		FHitResult hitInfo;
		FVector originLoc = player->rightHand->GetComponentLocation();
		FCollisionObjectQueryParams objectParams;
		objectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel2);

		FCollisionQueryParams params;
		params.AddIgnoredActor(player);

		bool bChecked = GetWorld()->SweepSingleByObjectType(hitInfo, originLoc, originLoc, FQuat::Identity, objectParams, FCollisionShape::MakeSphere(30), params);

		if (bChecked)
		{
			currentObj = Cast<ASugarSpoon>(hitInfo.GetActor());
			//UE_LOG(LogTemp, Warning, TEXT("%s(%d) - Hit Actor: %s"), *FString(__FUNCTION__), __LINE__, *hitInfo.GetActor()->GetActorNameOrLabel());

			if (currentObj != nullptr)
			{
				currentObj->OnGrabbed(player->rightHand);


			}
		}
	}

}

void UEJGrabComponent::ReleaseObject()
{
}

