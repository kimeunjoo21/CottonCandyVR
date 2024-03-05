// Fill out your copyright notice in the Description page of Project Settings.


#include "EJGrabComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EJVRPlayer.h"
#include "SugarSpoon.h"
#include "EarActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "CottonCandyActor.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Components/TextRenderComponent.h"



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

	pickUpEar = nullptr;
}


// Called every frame
void UEJGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...


	//������ ��Ʈ�ѷ��� ��ġ ��ȭ���� �����Ѵ�.
	previousLocation_rightCon = currentLocation_rightCon;
	currentLocation_rightCon = player->rightHand->GetComponentLocation();

	//FVector deltaDirection = currentLocation_rightCon - previousLocation_rightCon;
	//UE_LOG(LogTemp, Warning, TEXT("delta length: %f"), deltaDirection.Length());

	//������ ��Ʈ�ѷ��� ȸ������ �����Ѵ�
	previousRotation_rightCon = currentRotation_rightCon;
	currentRotation_rightCon = player->rightHand->GetComponentQuat();


	if(bMaking) makeBigger();
}

void UEJGrabComponent::SetupPlayerInputComponent(UEnhancedInputComponent* PlayerInputComponent, TArray<class UInputAction*> inputs)
{

	PlayerInputComponent->BindAction(inputs[1], ETriggerEvent::Started, this, &UEJGrabComponent::GrabObject);
	PlayerInputComponent->BindAction(inputs[1], ETriggerEvent::Completed, this, &UEJGrabComponent::ReleaseObject);

	PlayerInputComponent->BindAction(inputs[0], ETriggerEvent::Started, this, &UEJGrabComponent::makeBigger);
	PlayerInputComponent->BindAction(inputs[0], ETriggerEvent::Completed, this, &UEJGrabComponent::makeStop);

	PlayerInputComponent->BindAction(inputs[5], ETriggerEvent::Started, this, &UEJGrabComponent::GrabEar);
	PlayerInputComponent->BindAction(inputs[5], ETriggerEvent::Completed, this, &UEJGrabComponent::ReleaseEar);


}

void UEJGrabComponent::GrabObject()
{
	
	if (currentObj == nullptr) {
		// 1. SweepTrace�� �̿��� ���
		FHitResult hitInfo;
		FVector originLoc = player->rightHand->GetComponentLocation();
		FCollisionObjectQueryParams objectParams;
		objectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel2);

		FCollisionQueryParams params;
		params.AddIgnoredActor(player);

		bool bChecked = GetWorld()->SweepSingleByObjectType(hitInfo, originLoc, originLoc, FQuat::Identity, objectParams, FCollisionShape::MakeSphere(30), params);
		DrawDebugSphere(GetWorld(), player->rightHand->GetComponentLocation(), 20, 30, FColor::Green, false, 0.5f, 0, 0.2f);

		if (bChecked)
		{
			
			currentObj = Cast<ASugarSpoon>(hitInfo.GetActor());
			UE_LOG(LogTemp, Warning, TEXT("%s(%d) - Hit Actor: %s"), *FString(__FUNCTION__), __LINE__, *hitInfo.GetActor()->GetActorNameOrLabel());

			if (currentObj != nullptr)
			{
				currentObj->OnGrabbed(player->rightHand);
				player->rightLog->SetText(FText::FromString(FString::Printf(TEXT("Touch Sugar"))));


			}
		}
	}

}

void UEJGrabComponent::ReleaseObject()
{

	// ���� ����ִ� ��ü�� �ִ��� Ȯ���Ѵ�.
	if (currentObj != nullptr) {

		//������ ��Ʈ�ѷ��� ��ġ ��ȭ���� ����Ѵ�.
		//FVector deltaDirection = currentLocation_rightCon - previousLocation_rightCon;

		//������ ��Ʈ�ѷ��� ȸ�� ��ȭ���� ����Ѵ�.
		//FQuat deltaRotation = currentRotation_rightCon - previousRotation_rightCon;
		//FQuat deltaRotation = currentRotation_rightCon * previousRotation_rightCon.Inverse();

		currentObj->OnReleased(player->GetActorLocation());
		currentObj = nullptr;
	}
	
}

void UEJGrabComponent::makeBigger()
{
	//index press �� ��
	bMaking = true;

	//UE_LOG(LogTemp, Warning, TEXT("777"));

	cottonCandy = Cast<ACottonCandyActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ACottonCandyActor::StaticClass()));


	// ������ ��Ʈ�ѷ��� ��ġ ��ȭ���� ����Ѵ�.
	FVector deltaDirection = currentLocation_rightCon - previousLocation_rightCon;

	//UE_LOG(LogTemp,Warning, TEXT("%f"), deltaDirection.Length());

	// �� ��� �� Ŀ����
	if (deltaDirection.Length() > 0.6) {

		if(radiusBigger.Length() < 0.7) 
		{
			radiusBigger += FVector(0.001f);
			player->rightLog->SetText(FText::FromString(FString::Printf(TEXT("Continue Stiring"))));
		}
		else {
			//radiusBigger =FVector(0.7f);
			player->rightLog->SetText(FText::FromString(FString::Printf(TEXT("Completed! Make Ear"))));
		}

		if (cottonCandy != nullptr) {
			cottonCandy->compMesh->SetRelativeScale3D(radiusBigger);
			UE_LOG(LogTemp, Warning, TEXT("radius : %f"), radiusBigger.Length());

		}
	}

}

void UEJGrabComponent::makeStop()
{
	bMaking = false;

	UE_LOG(LogTemp, Warning, TEXT("stop making"));

}

void UEJGrabComponent::GrabEar()
{
	

	if (pickUpEar == nullptr) {

		// 1. SweepTrace�� �̿��� ���

		FHitResult hitInfo;
		FVector originLocForEar = player->leftHand->GetComponentLocation();
		FCollisionObjectQueryParams objectParams;
		objectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel2);

		FCollisionQueryParams params;
		params.AddIgnoredActor(player);

		bool bEarChecked = GetWorld()->SweepSingleByObjectType(hitInfo, originLocForEar, originLocForEar, FQuat::Identity, objectParams, FCollisionShape::MakeSphere(30), params);
		DrawDebugSphere(GetWorld(), player->leftHand->GetComponentLocation(), 20, 30, FColor::Green, false, 0.5f, 0, 0.2f);


		if (bEarChecked)
		{

			pickUpEar = Cast<AEarActor>(hitInfo.GetActor());
			UE_LOG(LogTemp, Warning, TEXT("%s(%d) - Hit Actor: %s"), *FString(__FUNCTION__), __LINE__, *hitInfo.GetActor()->GetActorNameOrLabel());

			if (pickUpEar != nullptr)
			{
				pickUpEar->OnGrabbed(player->leftHand);
				

			}
		}
	}
}

void UEJGrabComponent::ReleaseEar()
{
	// ���� ����ִ� ��ü�� �ִ��� Ȯ���Ѵ�.
	if (pickUpEar != nullptr) {

		//������ ��Ʈ�ѷ��� ��ġ ��ȭ���� ����Ѵ�.
		//FVector deltaDirection = currentLocation_rightCon - previousLocation_rightCon;

		//������ ��Ʈ�ѷ��� ȸ�� ��ȭ���� ����Ѵ�.
		//FQuat deltaRotation = currentRotation_rightCon - previousRotation_rightCon;
		//FQuat deltaRotation = currentRotation_rightCon * previousRotation_rightCon.Inverse();

		pickUpEar->OnReleased(currentObj->earScene->GetComponentLocation());
		pickUpEar = nullptr;


	}

}

