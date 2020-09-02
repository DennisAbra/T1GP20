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
	class USceneComponent* ParentLock;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PearlGateLock")
	class UStaticMeshComponent* LockMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PearlGateLock")
	class UBoxComponent* KeyCollisionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PearlGateLock")
	class UStaticMeshComponent* KeyMeshCheck;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
