// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "PlayerScripts/Interactable.h"
#include "Item.h"
#include "FirstPersonController.generated.h"

UCLASS()
class T1GP20_API AFirstPersonController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstPersonController();

	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* CurrentHeldItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* FirstPersonCamera;

	UPROPERTY(EditAnywhere)
	float Sensitivity = 1;

	UPROPERTY(EditAnywhere)
	float AirControl = 5;

	UPROPERTY(EditAnywhere)
	float MaxLookUpRange = 70;

	UPROPERTY(EditAnywhere)
	float MaxLookDownRange = 90;

	UPROPERTY(EditAnywhere)
	bool bInvertLook = false;

	UPROPERTY(BlueprintReadWrite)
	bool bIsHoldingItem;

	UPROPERTY(BlueprintReadWrite)
	bool bIsInspectingItem;

	UFUNCTION(BlueprintCallable, Category = "Inspect")
	void Inspect();

	UFUNCTION(BlueprintCallable, Category = "Inspect")
	void StopInspect();

private:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//void Interact();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveX(float Input);
	void MoveY(float Input);
	void LookX(float Input);
	void LookY(float Input);

};
