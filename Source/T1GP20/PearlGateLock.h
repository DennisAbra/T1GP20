// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PearlGateLock.generated.h"

UCLASS()
class T1GP20_API APearlGateLock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APearlGateLock();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PearlGateLock")
	USceneComponent* ParentLock;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PearlGateLock")
	class UStaticMeshComponent* LockMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PearlGateLock")
	class UStaticMeshComponent* KeyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateLock")
	FRotator SlotRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateLock")
	float AcceptableRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateLock")
	float SelfDestroyDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateLock")
	class APearlyGate* PearlyGate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateLock | Sound")
	class USoundCue* UnLockSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateLock | Sound", meta = (EditCondition = "UnLockSound != nullptr"))
	float UnLockSoundVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateLock | Sound", meta = (EditCondition = "UnLockSound != nullptr"))
	float DelayPlaySound;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool bHasPlayedSound = false;

public:	
	void RotateLock(FRotator Rotation);
	void CheckLockRotation();

	UFUNCTION()
	void PlayUnLockSound();
	FTimerHandle DestroyTimerHandle;
	FTimerHandle DelayPlaySoundTimerHandle;
	bool bIsDestroyed;
private:
	void SnapToRotation();
	void EmitPuzzleCompleteSignal();
	void Disappear();
};
