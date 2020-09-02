// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JigsawPieceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class T1GP20_API UJigsawPieceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJigsawPieceComponent();

	UPROPERTY()
	FVector FinalPosition;

	UPROPERTY()
	FRotator FinalRotation;

	UPROPERTY()
	bool bInRightPosition = false;

	UPROPERTY(EditAnywhere)
	float PositionMarginal = 10;

	UPROPERTY(EditAnywhere)
	float RotationMarginal = 10;

	UPROPERTY(EditAnywhere)
	bool bShouldIgnoreRotation = false;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool TestPosition(FTransform CurrentTransform);

	UFUNCTION(BlueprintCallable)
	void SetFinalTransform(FTransform FinalTransform);

	UFUNCTION(BlueprintCallable)
	void SnapIntoPlace();

		
};
