// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VRPlayer.generated.h"

UCLASS()
class COTTONCANDYVR_API AVRPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	public: 

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UCameraComponent* cameraComp;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UStaticMeshComponent* headMesh;



	/*UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UMotionControllerComponent* rightMotion;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class USkeletalMeshComponent* rightHand;*/

};
