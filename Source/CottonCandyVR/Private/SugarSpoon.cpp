// Fill out your copyright notice in the Description page of Project Settings.


#include "SugarSpoon.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/Scene.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SceneComponent.h>

// Sets default values
ASugarSpoon::ASugarSpoon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);
	//boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	boxComp->SetCollisionProfileName(FName("PickUpActor"));
	boxComp->SetBoxExtent(FVector(50));
	boxComp->SetWorldScale3D(FVector(0.05f, 0.05f, 0.4f));
	boxComp->SetSimulatePhysics(true);
	boxComp->SetEnableGravity(true);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//meshComp->SetRelativeLocation(FVector(0, 0, -50));

	sugarScene = CreateDefaultSubobject<USceneComponent>(TEXT("Spoon Tip"));
	sugarScene->SetupAttachment(meshComp);
	sugarScene->SetRelativeLocation(FVector(0,0,51));

}

// Called when the game starts or when spawned
void ASugarSpoon::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void ASugarSpoon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASugarSpoon::OnGrabbed(USkeletalMeshComponent* handMeshComp)
{
	UE_LOG(LogTemp, Warning, TEXT("OnGravved"));
	boxComp->SetSimulatePhysics(false);
	// 1. 잡을 당시의 간격 위치 값(월드 좌표 기준)을 그대로 유지하면서 붙이도록 설정한다.
	FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
	AttachToComponent(handMeshComp, attachRules);

}

void ASugarSpoon::OnReleased(FVector deltaDir)
{
	// 1.특정 액터로부터 자신을 분리한다.
	FDetachmentTransformRules detachRules = FDetachmentTransformRules::KeepWorldTransform;
	DetachFromActor(detachRules);
	//2. 떨어진 물체의 물리효과를 켜준다.
	boxComp->SetSimulatePhysics(true);

}


