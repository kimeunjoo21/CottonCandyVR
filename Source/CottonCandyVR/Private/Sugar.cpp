// Fill out your copyright notice in the Description page of Project Settings.


#include "Sugar.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h>
#include "SugarSpoon.h"
#include "CottonCandyMaker.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
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

	
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASugar::OnScoop);

	maker = UGameplayStatics::GetActorOfClass(GetWorld(), ACottonCandyMaker::StaticClass());

	up = GetActorLocation() + FVector(0, 0, 50);
}

// Called every frame
void ASugar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bMoveStart) Move();
}


void ASugar::Scoop()
{

}

void ASugar::ScoopOut()
{
	bMoveStart = false;
	Destroy();
}

void ASugar::OnScoop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

	//UE_LOG(LogTemp,Warning,TEXT("555"));
	sphereComp->SetSimulatePhysics(false);

	bMoveStart = true;

	
}

void ASugar::Move()
{
	
	if (ratioU < 1) {
		ratioU += GetWorld()->GetDeltaSeconds() * 0.8;
		if (ratioU >= 1) ratioU = 1;
		FVector moveUp = FMath::Lerp(GetActorLocation(), up, ratioU);
		SetActorLocation(moveUp);

		//UE_LOG(LogTemp,Warning,TEXT("ratioU : %f"), ratioU);
	}

	
	if (ratioU == 1 && ratioS < 1) {
		//UE_LOG(LogTemp, Warning, TEXT("ratioS : %f"), ratioS);

		FVector straight = maker->GetActorLocation() + FVector(0, 0, 50);
		ratioS += GetWorld()->GetDeltaSeconds() * 0.4;
		if (ratioS >= 1) ratioS = 1;
		FVector moveStraigh = FMath::Lerp(GetActorLocation(), straight, ratioS);
		SetActorLocation(moveStraigh);

	}
	
	if (ratioS == 1) {
		
		//UE_LOG(LogTemp, Warning, TEXT("ratioD : %f"), ratioD);


		FVector down = maker->GetActorLocation() + FVector(0, 0, 15);
		ratioD += GetWorld()->GetDeltaSeconds() * 0.8;
		if (ratioD > 1) ratioD = 1;
		FVector moveDown = FMath::Lerp(GetActorLocation(), down, ratioD);
		SetActorLocation(moveDown);

	}
	

}

