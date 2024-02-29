// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidgetActor.h"
#include "Components/WidgetComponent.h"

// Sets default values
AMenuWidgetActor::AMenuWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(rootComp);

	MenuWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Menu Widget Component"));
	MenuWidgetComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMenuWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMenuWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

