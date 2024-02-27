// Fill out your copyright notice in the Description page of Project Settings.


#include "UILineActor.h"
#include "NiagaraComponent.h"

// Sets default values
AUILineActor::AUILineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);

	lineFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("UIInteraciton Line Effect"));
	lineFX->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AUILineActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUILineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

