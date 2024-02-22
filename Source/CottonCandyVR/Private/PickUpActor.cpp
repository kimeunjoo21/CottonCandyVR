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

	// 1. ���� ����� ���� ��ġ ��(���� ��ǥ ����)�� �״�� �����ϸ鼭 ���̵��� �����Ѵ�.
	FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
	AttachToComponent(handMeshComp, attachRules);

	//// 2. �� �޽��� ���� ��ġ�� ���缭 �ڽ��� �����Ѵ�.
	//FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

	//AttachToComponent(handMeshComp, attachRules, FName("GrabPoint"));
	//SetActorRelativeLocation(offsetLocation);
	//SetActorRelativeRotation(offsetRotation);
}

void APickUpActor::OnReleased(FVector deltaDir)
{
	// 1. Ư�� ���ͷκ��� �ڽ����и���
	FDetachmentTransformRules detachRules = FDetachmentTransformRules::KeepWorldTransform;
	DetachFromActor(detachRules);

	// 2. ������ ��ü�� ���� ȿ�� ���ֱ�
	boxComp->SetSimulatePhysics(true);

}

