// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sugar.generated.h"

UCLASS()
class COTTONCANDYVR_API ASugar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASugar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:

	UPROPERTY(VisibleAnywhere, Category = "MySettings")
	class USphereComponent* sphereComp;
	UPROPERTY(VisibleAnywhere, Category = "MySettings")
	class UStaticMeshComponent* meshComp;

	UPROPERTY(VisibleAnywhere, Category = "MySettings")
	class ASugarSpoon* sugarSpoon;
	UPROPERTY(VisibleAnywhere, Category = "MySettings")
	class AEJVRPlayer* player;

	void Scoop();
	void ScoopOut();

	UFUNCTION()
	void OnScoop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
