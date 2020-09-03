// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CryptDoor.generated.h"

UCLASS()
class T1GP20_API ACryptDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACryptDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	bool bLibraryComplete = false;
	bool bSacrificialComplete = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void LibraryPuzzleComplete();

	UFUNCTION(BlueprintCallable)
	void SacrificialPuzzleComplete();

	UFUNCTION(BlueprintImplementableEvent)
	void OpenDoor();

	void TryOpenDoor();

};
