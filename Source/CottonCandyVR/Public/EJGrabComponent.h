// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EJGrabComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COTTONCANDYVR_API UEJGrabComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEJGrabComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent, TArray<class UInputAction*> inputs);

private:

	class AEJVRPlayer* player;
	class ASugarSpoon* currentObj;
	class ACottonCandyActor* cottonCandy;
	class AEarActor* pickUpEar;
	FVector currentLocation_rightCon;
	FVector previousLocation_rightCon;
	FQuat currentRotation_rightCon;
	FQuat previousRotation_rightCon;

	FVector radiusBigger = FVector(0.1f);


	UPROPERTY(EditAnywhere, Category = "MySettings")
	float throwPower = 500;

	bool bMaking = false;

	void GrabObject();
	void ReleaseObject();

	UFUNCTION(BlueprintCallable)
	void makeBigger();

	void makeStop();

	void GrabEar();
	void ReleaseEar();

};
