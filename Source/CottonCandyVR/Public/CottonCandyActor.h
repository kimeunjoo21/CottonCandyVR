// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CottonCandyActor.generated.h"

UCLASS()
class COTTONCANDYVR_API ACottonCandyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACottonCandyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class USphereComponent* compSphere;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compMesh;

// 	UPROPERTY(VisibleAnywhere, Category = "MySettings")
// 	class ASugarSpoon* sugarSpoon;


};
