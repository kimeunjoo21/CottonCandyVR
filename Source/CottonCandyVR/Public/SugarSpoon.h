// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SugarSpoon.generated.h"

UCLASS()
class COTTONCANDYVR_API ASugarSpoon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASugarSpoon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(VisibleAnywhere, Category="MySettings")
	class UBoxComponent* boxComp;

	UPROPERTY(VisibleAnywhere, Category = "MySettings")
	class UStaticMeshComponent* meshComp;

	
	UPROPERTY(EditAnywhere, Category = "MySettings")
	FVector offsetLocation;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	FRotator offsetRotation;

public:
	void OnGrabbed(class USkeletalMeshComponent* handMeshComp);
	void OnReleased(FVector deltaDir);


};
