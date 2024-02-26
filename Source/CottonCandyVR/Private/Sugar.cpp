// Fill out your copyright notice in the Description page of Project Settings.


#include "Sugar.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h>
#include "SugarSpoon.h"
#include "EJVRPlayer.h"
// Sets default values
ASugar::ASugar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SetRootComponent(sphereComp);
	sphereComp->SetSphereRadius(8.5f);
	sphereComp->SetCollisionProfileName(FName("PickUpActor"));


	sphereComp->SetSimulatePhysics(true);
	sphereComp->SetEnableGravity(true);


	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetWorldScale3D(FVector(0.165f));
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void ASugar::BeginPlay()
{
	Super::BeginPlay();

	player = GetOwner<AEJVRPlayer>();
	
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASugar::OnScoop);
}

// Called every frame
void ASugar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASugar::Scoop()
{

}

void ASugar::ScoopOut()
{

}

void ASugar::OnScoop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

	UE_LOG(LogTemp,Warning,TEXT("555"));
	AttachToComponent(player->rightHand, attachRules, FName("GrabPoint"));
	sphereComp->SetSimulatePhysics(false);

}

