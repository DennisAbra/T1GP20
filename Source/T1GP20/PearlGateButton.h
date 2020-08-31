// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "PearlGateButton.generated.h"

UENUM(BlueprintType)
enum class ERotationWays : uint8
{
	ERW_Pitch	UMETA(DisplayName = "Pitch"),
	ERW_Yaw		UMETA(DisplayName = "Yaw"),
	ERW_Roll	UMETA(DisplayName = "Roll"),

	ERW_Max		UMETA(DisplayName = "DefaultMax")
};
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateButton")
	ERotationWays RotateDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateButton")
	float DegreeToRotate;

protected:
	void BeginPlay() override;

public:
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

private:
	FVector InitialLocation;
	FRotator InitialRotation;
};
