// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "PearlGateButton.generated.h"

/**
 * 
 */
UCLASS()
class T1GP20_API APearlGateButton : public AItem
{
	GENERATED_BODY()
	
public:
	APearlGateButton();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PearlGateButton")
	UStaticMeshComponent* PuzzleButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PearlGateButton")
	USceneComponent* PuzzleParent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PearlGateButton")
	class UAudioComponent* PuzzleAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateButton")
	float InterpSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PearlGateButton")
	class AFirstPersonController* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateButton")
	bool bActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateButton | Puzzle")
	class APearlGateLock* PearlGateLock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateButton | Sound")
	class USoundCue* ActivatePuzzleSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateButton | Sound", meta = (EditCondition = "ActivatePuzzleSound != nullptr"))
	float ActivateSoundVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateButton | Sound")
	USoundCue* RollingSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateButton | Sound", meta = (EditCondition = "RollingSound != nullptr"))
	float RollingSoundVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateButton | Sound")
	USoundCue* PuzzleCorrectSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateButton | Sound", meta = (EditCondition = "DisactivatePuzzleSound != nullptr"))
	float CorrectSoundVolume;

protected:
	void BeginPlay() override;

public:
	void Tick(float DeltaTime) override;
	void Interact_Implementation() override;
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "PearlGateButton")
	void RotateObject();

	UFUNCTION(BlueprintCallable)
	void SetPuzzleActivate();

	UFUNCTION(BlueprintCallable)
	int32 GetRotationIncrement(FVector HitLocation, FVector2D MouseInputValue);
	UFUNCTION(BlueprintCallable)
	void EmitRotationSignal();
	UFUNCTION(BlueprintCallable)
	void PlayRollingSound();
	UFUNCTION(BlueprintCallable)
	void StopPlayRollingSound();
private:
	FRotator SlotRotation;
	float AcceptableRange;
	bool bOnOverlapping;
	bool bMouseLeftClickToggle;
	bool bObjectRotationActivate;
	bool bHasPlayedCorrectSound;
	void SetActivateObjectRotation(bool Active);
	
	void StartInteract();
	void FinishInteract();
};
