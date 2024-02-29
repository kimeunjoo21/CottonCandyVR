// Fill out your copyright notice in the Description page of Project Settings.


#include "CottonCandyActor.h"
#include "NiagaraComponent.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>
#include "SugarSpoon.h"
#include <Kismet/GameplayStatics.h>


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

	//player = Cast<AEJVRPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
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


	previousRotation_rightCon = currentRotation_rightCon;
	//currentRotation_rightCon = player->rightHand->GetComponentQuat();



	radiusBigger += FVector(0.001f);
	UE_LOG(LogTemp,Warning,TEXT("%f"),radiusBigger.Length());
	compMesh->SetRelativeScale3D(radiusBigger);
}

void ACottonCandyActor::SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent, TArray<class UInputAction*> inputs)
{

}

