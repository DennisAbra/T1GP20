// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerScripts/Interactable.h"
#include "Clock.generated.h"

UENUM(BlueprintType)
enum class ERotateDirection : uint8
{
	ERD_Pitch	UMETA(DisplayName = "Pitch"),
	ERD_Yaw		UMETA(DisplayName = "Yaw"),
	ERD_Roll	UMETA(DisplayName = "Roll"),

	ERD_Max		UMETA(DisplayName = "DefaultMax")
};
UCLASS()
class T1GP20_API AClock : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClock();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Clock")
	class UStaticMeshComponent* ClockMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Clock")
	USceneComponent* HourHandParent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Clock")
	UStaticMeshComponent* HourHandMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Clock")
	USceneComponent* MinuteHandParent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Clock")
	UStaticMeshComponent* MinuteHandMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Clock")
	USceneComponent* SecondHandParent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Clock")
	UStaticMeshComponent* SecondHandMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock", meta = (ClampMin = "0", ClampMax = "12", UIMin = "0", UIMax = "12"))
	int32 StartHour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock", meta = (ClampMin = "0", ClampMax = "60", UIMin = "0", UIMax = "60"))
	int32 StartMinute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock")
	int32 MaxSecondToEndTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Clock")
	ERotateDirection RotateDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Clock")
	int32 TimeTickingCounter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock | Sound")
	bool bShouldTickSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock | Sound", meta = (EditCondition = "bShouldTickSound"))
	class USoundCue* ClockTickingSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock | Sound", meta = (EditCondition = "bShouldTickSound"))
	float TickingSoundVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock | Sound")
	bool bShouldRingBellSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock | Sound", meta = (EditCondition = "bShouldRingBellSound"))
	USoundCue* ClockBellSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock | Sound", meta = (EditCondition = "bShouldRingBellSound"))
	float BellSoundVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock | Sound", meta = (EditCondition = "bShouldRingBellSound"))
	float SecondsToRingBellInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock")
	class AFirstPersonController* Player;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartClockTicking(ERotateDirection Direction);

	UFUNCTION(BlueprintImplementableEvent, Category = "Clock")
	void TimesUp();

	UFUNCTION(BlueprintImplementableEvent, Category = "Clock")
	void BellRing();
private:
	void SetStartTime(); 
	float SecondHandRotateDegreePerSec;
	float MinuteHandRotateDegreePerSec;
	float HourHandRotateDegreePerSec;
	float RingBellCounter;
};
