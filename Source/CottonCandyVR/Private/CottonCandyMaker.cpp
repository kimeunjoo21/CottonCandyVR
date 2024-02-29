// Fill out your copyright notice in the Description page of Project Settings.


#include "CottonCandyMaker.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "CottonCandyActor.h"
#include "SugarSpoon.h"

// Sets default values
ACottonCandyMaker::ACottonCandyMaker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50));
	boxComp->SetCollisionProfileName(FName("CottonCandyMaker"));


	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ConstructorHelpers::FClassFinder<ACottonCandyActor> tempCandy(TEXT("/Script/Engine.Blueprint'/Game/KEJ/BluePrints/BP_CottonCandyActor.BP_CottonCandyActor_C'"));
	if (tempCandy.Succeeded())
	{
		cottonCandyActor = tempCandy.Class;
	}
	
}

// Called when the game starts or when spawned
void ACottonCandyMaker::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ACottonCandyMaker::OnOverlap);

	//cotton = UGameplayStatics::GetActorOfClass(GetWorld(), ACottonCandyActor::StaticClass());
	sugarSpoon = UGameplayStatics::GetActorOfClass(GetWorld(), ASugarSpoon::StaticClass());
	spoon = Cast<ASugarSpoon>(sugarSpoon);

}

// Called every frame
void ACottonCandyMaker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACottonCandyMaker::OnOverlap(UPrimitiveComponent* abc, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains(TEXT("SugarSpoon")))
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnActor"));


		FVector spoonTipLoc = spoon->sugarScene->GetComponentLocation();
		FRotator spoonTipRot = spoon->sugarScene->GetRelativeRotation();		
		GetWorld()->SpawnActor<ACottonCandyActor>(cottonCandyActor, spoonTipLoc, spoonTipRot);
		
	}

}

