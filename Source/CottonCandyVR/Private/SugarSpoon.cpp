// Fill out your copyright notice in the Description page of Project Settings.


#include "SugarSpoon.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"


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
	boxComp->SetSimulatePhysics(false);
	// 1. ���� ����� ���� ��ġ ��(���� ��ǥ ����)�� �״�� �����ϸ鼭 ���̵��� �����Ѵ�.
	FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
	AttachToComponent(handMeshComp, attachRules);

}

void ASugarSpoon::OnReleased(FVector deltaDir, float throwThreshold, FVector deltaRot)
{
}

