// Fill out your copyright notice in the Description page of Project Settings.


#include "EarActor.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include "CottonCandyActor.h"

// Sets default values
AEarActor::AEarActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체
	compSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	SetRootComponent(compSphere);
	compSphere->SetSphereRadius(3);
	compSphere->SetCollisionProfileName(TEXT("BlockAll"));

	// 모양
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	compMesh->SetupAttachment(RootComponent);
	compMesh->SetRelativeScale3D(FVector(0.1f));
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));

}

// Called when the game starts or when spawned
void AEarActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEarActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

