// Fill out your copyright notice in the Description page of Project Settings.


#include "CottonCandyActor.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>
#include "SugarSpoon.h"
#include <Kismet/GameplayStatics.h>
#include "EJVRPlayer.h"


// Sets default values
ACottonCandyActor::ACottonCandyActor()
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

	spoon  = Cast<ASugarSpoon>(UGameplayStatics::GetActorOfClass(GetWorld(), ASugarSpoon::StaticClass()));


}

// Called when the game starts or when spawned
void ACottonCandyActor::BeginPlay()
{
	Super::BeginPlay();

	compSphere->SetSimulatePhysics(false);
	FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;



	if (spoon != nullptr) {
		
		//ASugarSpoon* bar = Cast<ASugarSpoon>(sugarSpoon);
		AttachToComponent(spoon->sugarScene, attachRules);
		//AttachToActor(bar, attachRules);
	}
	
}

// Called every frame
void ACottonCandyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}



