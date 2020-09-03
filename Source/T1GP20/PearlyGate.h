// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PearlyGate.generated.h"

UCLASS()
class T1GP20_API APearlyGate : public AActor
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGate")
	TMap<class APearlGateLock*, bool> PearlGateLockList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateLock")
	bool bGateIsOpen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGate | Sound")
	class USoundCue* DoorOpenSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGate | Sound")
	USoundCue* DoorCloseSound;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintImplementableEvent, Category = "PearlyGate")
	void OpenGate();

	UFUNCTION(BlueprintImplementableEvent, Category = "PearlyGate")
	void CloseGate();

	UFUNCTION(BlueprintCallable, Category = "PearlyGate")
	void UpdateDoorRotation(FRotator LeftDoor, FRotator RightDoor);

	void UpdateGateLockStatus(APearlGateLock* Key, bool Value);

	bool bPuzzleComplete;
private:
	FRotator InitialLeftDoorRotation;
	FRotator InitialRightDoorRotation;
	bool CheckAllLockStatus();
	void TriggerOpenGate();
};
