// Fill out your copyright notice in the Description page of Project Settings.


#include "CottonCandyActor.h"
#include "NiagaraComponent.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>
#include "SugarSpoon.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>


// Sets default values
ACottonCandyActor::ACottonCandyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// 충돌체
	compSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	SetRootComponent(compSphere);
	compSphere->SetSphereRadius(13);
	compSphere->SetCollisionProfileName(TEXT("BlockAll"));

	// 모양
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	compMesh->SetupAttachment(RootComponent);
	compMesh->SetRelativeScale3D(FVector(0.26f));
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));

}

// Called when the game starts or when spawned
void ACottonCandyActor::BeginPlay()
{
	Super::BeginPlay();

	compSphere->SetSimulatePhysics(false);
	FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

	AActor* sugarSpoon = UGameplayStatics::GetActorOfClass(GetWorld(), ASugarSpoon::StaticClass());
	if (sugarSpoon != nullptr) {
		
		ASugarSpoon* bar = Cast<ASugarSpoon>(sugarSpoon);
		AttachToActor(bar, attachRules);
	}
	
}

// Called every frame
void ACottonCandyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

