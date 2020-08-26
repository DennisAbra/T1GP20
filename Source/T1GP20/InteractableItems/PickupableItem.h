// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../PlayerScripts/Interactable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupableItem.generated.h"

UENUM()
enum Shape
{
	Round,
	Square,
	Banana,
	Carrot
};

UCLASS()
class T1GP20_API APickupableItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	


	// Sets default values for this actor's properties
	APickupableItem();

	UPROPERTY(EditAnywhere)
	int Weight = 10;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<Shape> _Shape;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void Interact_Implementation() override;

};
