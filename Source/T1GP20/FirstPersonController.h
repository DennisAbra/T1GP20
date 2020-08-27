// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "FirstPersonController.generated.h"

UCLASS()
class T1GP20_API AFirstPersonController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstPersonController();

	UPROPERTY(EditAnywhere)
	float Sensitivity = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SprintSlowSensMultiplyer = 0.15f;

	UPROPERTY(EditAnywhere)
	float AirControl = 5;

	UPROPERTY(EditAnywhere)
<<<<<<< Updated upstream
	float MaxLookRange = 65;
=======
	float MaxLookUpRange = 70;
	
	UPROPERTY(EditAnywhere)
	float MaxLookDownRange = 90;
>>>>>>> Stashed changes

	UPROPERTY(EditAnywhere)
	bool bInvertLook = false;

<<<<<<< Updated upstream
=======
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Walkspeed = 500;


	UPROPERTY(BlueprintReadWrite)
	bool bIsSprinting = false;

	UPROPERTY(BlueprintReadWrite)
	bool bIsCrouching = false;
private:
	float Sprintspeed;
	float CrouchSpeed;

>>>>>>> Stashed changes

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

<<<<<<< Updated upstream
=======
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* FirstPersonCamera;
	
	

>>>>>>> Stashed changes
private:
	void MoveX(float Input);
	void MoveY(float Input);
	void LookX(float Input);
	void LookY(float Input);

<<<<<<< Updated upstream
	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* FirstPersonCamera;

	void Crouch();
	void StopCrouch();
=======
	void Sprint();
	void StopSprint();
	void Crouch();
	void StopCrouch();

>>>>>>> Stashed changes
};
