// Fill out your copyright notice in the Description page of Project Settings.


#include "EarActor.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "SugarSpoon.h"

// Sets default values
AEarActor::AEarActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �浹ü
	compSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	SetRootComponent(compSphere);
	compSphere->SetSphereRadius(15);
	compSphere->SetCollisionProfileName(FName("PickUpActor"));

	// ���
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	compMesh->SetupAttachment(RootComponent);
	compMesh->SetRelativeScale3D(FVector(3.0f));
	compMesh->SetRelativeLocation(FVector(0, -90, -20));
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));

	
}

// Called when the game starts or when spawned
void AEarActor::BeginPlay()
{
	Super::BeginPlay();
	
	spoon = Cast<ASugarSpoon>(UGameplayStatics::GetActorOfClass(GetWorld(), ASugarSpoon::StaticClass()));

}

// Called every frame
void AEarActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEarActor::OnGrabbed(USkeletalMeshComponent* handMeshComp)
{
	UE_LOG(LogTemp, Warning, TEXT("OnGrabbed"));
	compSphere->SetSimulatePhysics(false);
	// 1. ���� ����� ���� ��ġ ��(���� ��ǥ ����)�� �״�� �����ϸ鼭 ���̵��� �����Ѵ�.
	FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
	AttachToComponent(handMeshComp, attachRules);

}

void AEarActor::OnReleased(FVector deltaDir)
{
	// 1.Ư�� ���ͷκ��� �ڽ��� �и��Ѵ�.
	FDetachmentTransformRules detachRules = FDetachmentTransformRules::KeepWorldTransform;
	DetachFromActor(detachRules);
	//2. ������ ��ü�� ����ȿ���� ���ش�.
	//compSphere->SetSimulatePhysics(true);

	FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
	
	if (spoon != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("ear attach?"));
		//ASugarSpoon* bar = Cast<ASugarSpoon>(sugarSpoon);
		AttachToComponent(spoon->earScene, attachRules);
		//AttachToActor(bar, attachRules);
	}
	
	
}

