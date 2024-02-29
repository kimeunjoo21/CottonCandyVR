// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CottonCandyMaker.generated.h"

UCLASS()
class COTTONCANDYVR_API ACottonCandyMaker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACottonCandyMaker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(VisibleAnywhere, Category="MySettings")
	class UBoxComponent* boxComp;

	UPROPERTY(VisibleAnywhere, Category = "MySettings")
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	TSubclassOf<class ACottonCandyActor> cottonCandyActor;

	UPROPERTY(EditAnywhere)
	AActor* cotton;
	UPROPERTY(EditAnywhere)
	AActor* sugarSpoon;

	UPROPERTY(VisibleAnywhere, Category = "MySettings")
	class ASugarSpoon* spoon;


public:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* abc, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//class ACottonCandyActor* cottonCandy;

};
