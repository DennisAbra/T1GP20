// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressurePad.generated.h"

UCLASS()
class T1GP20_API APressurePad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressurePad();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pressure Pad")
	class UBoxComponent* TriggerBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pressure Pad")
	class UStaticMeshComponent* ScalePad;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pressure Pad")
	UStaticMeshComponent* Door;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pressure Pad | Item")
	bool bActiveWeightCheck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pressure Pad | Item", meta = (EditCondition = "bActiveWeightCheck"))
	float MinWeightToTrigger;

	UPROPERTY(EditAnywhere, blueprintReadWrite, Category = "Pressure Pad | Item", meta = (EditCondition = "bActiveWeightCheck"))
	float MaxWeightToTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pressure Pad | Item | ParticleSystem")
	class UParticleSystem* PassEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pressure Pad | Item | Sound")
	class USoundCue* PassSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pressure Pad | Item")
	bool bActiveItemCheck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pressure Pad | Item", meta = (EditCondition = "bActiveItemToCheck" ))
	class AItem* KeyItem;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Pressure Pad")
	void OpenDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "Pressure Pad")
	void CloseDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "Pressure Pad")
	void LowerScalePad();

	UFUNCTION(BlueprintImplementableEvent, Category = "Pressure Pad")
	void RaiseScalePad();

	UFUNCTION(BlueprintCallable, Category = "Pressure Pad")
	void UpdateDoorLocation(FVector Location);

	UFUNCTION(BlueprintCallable, Category = "Pressure Pad")
	void UpdateScalePadLocation(FVector Location);

private:
	FVector InitialDoorLocation;
	FVector InitialScalePadLocation;
	bool IsDoorOpened;
	void TriggerPass();
	void BackToUnTrigger();
};
