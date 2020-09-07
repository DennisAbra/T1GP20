// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "PlayerScripts/Interactable.h"
#include "Item.h"
#include "FirstPersonController.generated.h"

class UCameraShake;

UCLASS()
class T1GP20_API AFirstPersonController : public ACharacter
{
	GENERATED_BODY()

public:
	AFirstPersonController();

	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* CurrentHeldItemCpp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* FirstPersonCamera;

	UPROPERTY(EditAnywhere, Category = "Settings | Mouse")
	float Sensitivity = 1;

	UPROPERTY(EditAnywhere, Category = "Settings | Mouse")
	float MaxLookUpRange = 70;

	UPROPERTY(EditAnywhere, Category = "Settings | Mouse")
	float MaxLookDownRange = 90;

	UPROPERTY(EditAnywhere, Category = "Settings | Mouse")
	bool bInvertLook = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | MovementStuff")
	float WalkSpeed = 275;

	UPROPERTY(EditAnywhere, Category = "Settings | MovementStuff")
	float Acceleration = 800;

	UPROPERTY(EditAnywhere, Category = "Settings | MovementStuff")
	float AirControl = 5;

	UPROPERTY(EditAnywhere, Category = "Settings | AutoSprint")
	float TimeUntilSprint = 3;

	UPROPERTY(EditAnywhere, Category = "Settings | AutoSprint")
	float WalkSpeedMultiplyer = 2.5;

	UPROPERTY(EditAnywhere, Category = "Settings | AutoSprint")
	float SprintAcceleration = 0.5;

	UPROPERTY(BlueprintReadWrite)
	bool bIsHoldingItem;

	UPROPERTY(BlueprintReadWrite)
	bool bIsInspectingItem;
	
	UPROPERTY(BlueprintReadWrite)
	bool bCurrentItemRotateOnly = false;

	UPROPERTY(BlueprintReadWrite)
	bool bMouseLook = true;

	UPROPERTY(BlueprintReadWrite)
	bool bCanMove = true;

	UFUNCTION(BlueprintCallable, Category = "Inspect")
	void Inspect();

	UFUNCTION(BlueprintCallable, Category = "Inspect")
	void StopInspect();


private:

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShake> CamShake;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "CameraShake")
	void ShakeItBaby();

private:
	FTimerHandle TimeUntilBoostHandle;

	void BoostStart();
	void BoostIncrease();

	void MoveX(float Input);
	void MoveY(float Input);
	void LookX(float Input);
	void LookY(float Input);
};
