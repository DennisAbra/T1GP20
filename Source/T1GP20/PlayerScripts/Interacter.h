// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactable.h"
#include "Interacter.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class T1GP20_API UInteracter : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteracter();

	UPROPERTY(EditAnywhere)
		float ShootingDistance = 250;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	AActor* TriggerInteract(FTransform RayOrigin, FVector ForwardVector);

		//Cache currentTarget in tick.
		// Do the actual interactions and such only on press
		//currentTarget should be accessible through blueprints
};
