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

	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent, TArray<class UInputAction*> inputs);


	UPROPERTY(EditAnywhere)
	class USphereComponent* compSphere;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compMesh;

	UPROPERTY(EditAnywhere)
	class AEJVRPlayer* player;

	UPROPERTY(VisibleAnywhere, Category = "MySettings")
	class ASugarSpoon* spoon;

	FVector radiusBigger = FVector(0.1f);

	FQuat currentRotation_rightCon;
	FQuat previousRotation_rightCon;


};
