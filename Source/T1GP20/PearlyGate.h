// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerScripts/Interactable.h"
#include "PearlyGate.generated.h"

UCLASS()
class T1GP20_API APearlyGate : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APearlyGate();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PearlyGate")
	class UStaticMeshComponent* DoorFrameMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PearlyGate")
	UStaticMeshComponent* LeftDoorMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PearlyGate")
	UStaticMeshComponent* RightDoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlyGate")
	TMap<class APearlGateLock*, bool> PearlGateLockList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlyGate")
	float DelayOpenGate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlyGate | Sound")
	class USoundCue* DoorOpenSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlyGate | Sound")
	USoundCue* DoorCloseSound;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "PearlyGate")
	void OpenGate();

	UFUNCTION(BlueprintImplementableEvent, Category = "PearlyGate")
	void CloseGate();

	UFUNCTION(BlueprintCallable, Category = "PearlyGate")
	void UpdateDoorRotation(FRotator LeftDoor, FRotator RightDoor);

	void UpdateGateLockStatus(APearlGateLock* Key, bool Value);

	UFUNCTION()
	void TriggerOpenGate();
	FTimerHandle OpenGateTimerHandle;
private:
	FRotator InitialLeftDoorRotation;
	FRotator InitialRightDoorRotation;
	bool CheckAllLockStatus();
};
