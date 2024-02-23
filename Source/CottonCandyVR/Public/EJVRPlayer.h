// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "EJVRPlayer.generated.h"

UCLASS()
class COTTONCANDYVR_API AEJVRPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEJVRPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UCameraComponent* cameraComp;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UStaticMeshComponent* headMesh;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UMotionControllerComponent* leftMotion;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class USkeletalMeshComponent* leftHand;


	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UMotionControllerComponent* rightMotion;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class USkeletalMeshComponent* rightHand;


	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UEJGrabComponent* grabComp;


	UPROPERTY(EditAnywhere, Category = "MySettings|Inputs")
	class UInputMappingContext* vrMapping;

	UPROPERTY(EditAnywhere, Category = "MySettings|Inputs")
	TArray<class UInputAction*> vrInputs;

	//¿À¸¥¼Õ
	float currentRightHandTrigger = 0;
	float rightIndexTouch = 0;
	float currentRightIndexTrigger = 0;
	float rightThumbUpTouch = 0;
	//¿Þ¼Õ
	float currentLeftHandTrigger = 0;
	float leftIndexTouch = 0;
	float currentLeftIndexTrigger = 0;
	float leftThumbUpTouch = 0;


private:
// 	void RightTriggerTouch(const FInputActionValue& val);
// 	void RightTriggerPress(const FInputActionValue& val);
// 	void RightTriggerValue(const FInputActionValue& val);
// 	void Move(const FInputActionValue& val);
// 	void Rotate(const FInputActionValue& val);
// 	void RightHandTriggerValue(const FInputActionValue& val);
// 	void RightIndexTouchValue(const FInputActionValue& val);
// 	void RightIndexTriggerValue(const FInputActionValue& val);
// 	void RightThumbupTouchValue(const FInputActionValue& val);
// 
// 	void LeftHandTriggerValue(const FInputActionValue& val);
// 	void LeftIndexTouchValue(const FInputActionValue& val);
// 	void LeftIndexTriggerValue(const FInputActionValue& val);
// 	void LeftThumbupTouchValue(const FInputActionValue& val);


};
