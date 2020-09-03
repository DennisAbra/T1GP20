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
	class UBoxComponent* KeyCollisionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PearlGateLock")
	class UStaticMeshComponent* KeyMeshCheck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateLock")
	FRotator SlotRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PearlGateLock")
	class APearlyGate* PearlyGate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void RotateLock(FRotator Rotation);
	void Disappear();

private:
	void SnapToRotaiton();
};
