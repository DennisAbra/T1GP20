// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerScripts/Interactable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class T1GP20_API AItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	/** Base shape collision */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item | Collision")
	class USphereComponent* CollisionVolume;

	/*** Base Mesh Component */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item | Mesh")
	class UStaticMeshComponent* ObjectMesh;

	/** Base pariticle effect with object */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Particles | Idle")
	class UParticleSystemComponent* IdleParticlesComponent;

	/** Base particle effect when overlaping the object*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Particles | Overlap")
	class UParticleSystem* OverlapParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	class USoundCue* OverlapSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Weight")
	bool bOverrideMassWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Weight", meta = (EditCondition = "bOverrideMassWeight"))
	float MassWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Other")
	bool bDefaultRotationOnPickup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Other")
	bool bOffCenterHoldingPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound", meta = (ToolTip = "0 = Default\n1 = Wood\n2 = Glass\n3 = GlassBreak\n 4 = Rock\n5 = Heavy Metal\n6 = Bone\n7 = Anchor(small thing)\n8 = Book"))
	int MaterialInt = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation() override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
