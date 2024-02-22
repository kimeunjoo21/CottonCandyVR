// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "VRPlayer_M.generated.h"

UCLASS()
class COTTONCANDYVR_API AVRPlayer_M : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRPlayer_M();

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

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UMotionControllerComponent* leftMotion;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings|Components")
	class USkeletalMeshComponent* leftHand;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UMotionControllerComponent* rightMotion;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings|Components")
	class USkeletalMeshComponent* rightHand;

	
	/* ----------------------------------------------------------- */
	UPROPERTY(EditAnywhere, Category = "MySettings|Inputs")
	class UInputMappingContext* vrMapping;

	UPROPERTY(EditAnywhere, Category = "MySettings|Inputs")
	TArray <class UInputAction*>  vrInputs;

	UPROPERTY(EditAnywhere, Category = "MySettings|Inputs")
	class UInputAction* ia_rightThumbStickAxis;

	UPROPERTY(EditAnywhere, Category = "MySettings|Inputs")
	class UInputAction* ia_leftThumbStickAxis;

private:
	void Move(const FInputActionValue& val);
	void Rotate(const FInputActionValue& val);
};
