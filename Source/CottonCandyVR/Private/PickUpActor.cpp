// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpActor.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/SkeletalMeshComponent.h>

// Sets default values
APickUpActor::APickUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);
	boxComp->SetCollisionProfileName(FName("PickUpActor"));
	//boxComp->SetBoxExtent(FVector(50));
	boxComp->SetSimulatePhysics(true);
	boxComp->SetEnableGravity(true);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

// Called when the game starts or when spawned
void APickUpActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUpActor::OnGrabbed(class USkeletalMeshComponent* handMeshComp)
{
	boxComp->SetSimulatePhysics(false);

	// 1. 잡을 당시의 간격 위치 값(월드 좌표 기준)을 그대로 유지하면서 붙이도록 설정한다.
	FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
	AttachToComponent(handMeshComp, attachRules);

	//// 2. 손 메시의 소켓 위치에 맞춰서 자신을 부착한다.
	//FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

	//AttachToComponent(handMeshComp, attachRules, FName("GrabPoint"));
	//SetActorRelativeLocation(offsetLocation);
	//SetActorRelativeRotation(offsetRotation);
}

void APickUpActor::OnReleased(FVector deltaDir)
{
	// 1. 특정 액터로부터 자신을분리함
	FDetachmentTransformRules detachRules = FDetachmentTransformRules::KeepWorldTransform;
	DetachFromActor(detachRules);

	// 2. 떨어진 물체의 물리 효과 켜주기
	boxComp->SetSimulatePhysics(true);

}

