// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "PearlGateButton.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EFaceDirection : uint8
{
	EFD_Front	UMETA(DisplayName = "Front"),
	EFD_Rright	UMETA(DisplayName = "Right"),
	EFD_Left	UMETA(DisplayName = "Left"),
	EFD_Back	UMETA(DisplayName = "Back"),

	EFD_MAX		UMETA(DisplayName = "Default_Max")
};
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateButton")
	EFaceDirection FaceDirection;

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

	UPROPERTY(BlueprintReadWrite)
	bool bOnOverlapping;

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
	void SetPuzzleActivate(bool Value);

	UFUNCTION(BlueprintCallable)
	int32 GetRotationIncrement(EFaceDirection Direction, FVector HitLocation, FVector2D MouseInputValue);

	UFUNCTION(BlueprintCallable)
	void EmitRotationSignal();

	UFUNCTION(BlueprintImplementableEvent)
	void IsNotInteracting();

	UFUNCTION(BlueprintImplementableEvent)
	void InteractWhenNotActivate();
private:
	FRotator SlotRotation;
	float AcceptableRange;
	bool bMouseLeftClickToggle;
	bool bObjectRotationActivate;
	bool bHasPlayedCorrectSound;

	/**
	* A Matrix to indicate how rolling-disc puzzle should rotate when player starts interaction.
	* The matrix stores Mouse Input X-value, Y-value, line trace hit location X-value and z-value as KEY.
	* 1 = less than 0, 2 = equal 0, 3 = more than 0, so KEY combination can be like 2212, it represents as:
	*         3            3           1           3 
	*    [MouseInputX, MouseInputY, HitPlaceX, HitPlaceZ]
	* And the VALUE of the matrix return 1 or -1 for telling rolling-disc should rotate in clockwise or in counterclockwise direction
	* if the key we search is not inside the matrix, return 0
	*/
	TMap<int32, int32> RollingOperationMatrix;
	void InitializeMatrix();

	void SetActivateObjectRotation(bool Active);
	void StartInteract();
	void FinishInteract();
};
