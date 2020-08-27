// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerDoor.generated.h"

UCLASS()
class T1GP20_API ATriggerDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerDoor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TriggerDoor")
	UStaticMeshComponent* ObjectMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TriggerDoor | Sound")
	class USoundCue* TriggerSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger Door | Pressure Pad")
	TMap <class APressurePad*,  bool>  PressurePadList;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintImplementableEvent, Category = "Pressure Pad")
	void OpenDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "Pressure Pad")
	void CloseDoor();

	UFUNCTION(BlueprintCallable, Category = "Pressure Pad")
	void UpdateDoorLocation(FVector Location);

	void UpdatePressurePadStatus(APressurePad* Key, bool Value);

	bool bIsDoorOpened;
private:
	FVector InitialDoorLocation;
	bool CheckAllPressurePadsValue();
	void TriggerOpenDoor();
};
