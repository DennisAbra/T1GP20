// Fill out your copyright notice in the Description page of Project Settings.


#include "PearlyGate.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
APearlyGate::APearlyGate()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFramMesh"));
	DoorFrameMesh->SetupAttachment(GetRootComponent());

	LeftDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoorMesh"));
	LeftDoorMesh->SetupAttachment(DoorFrameMesh);

	RightDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoorMesh"));
	RightDoorMesh->SetupAttachment(DoorFrameMesh);
}

// Called when the game starts or when spawned
void APearlyGate::BeginPlay()
{
	Super::BeginPlay();
	
	InitialLeftDoorRotation = LeftDoorMesh->GetComponentRotation();
	InitialRightDoorRotation = RightDoorMesh->GetComponentRotation();
}

void APearlyGate::UpdateDoorRotation(FRotator LeftDoor, FRotator RightDoor)
{
	FRotator LeftDoorNewRotation = InitialLeftDoorRotation;
	LeftDoorNewRotation += LeftDoor;
	LeftDoorMesh->SetWorldRotation(LeftDoorNewRotation);

	FRotator RightDoorNewRotation = InitialRightDoorRotation;
	RightDoorNewRotation += RightDoor;
	RightDoorMesh->SetWorldRotation(RightDoorNewRotation);
}

void APearlyGate::UpdateGateLockStatus(APearlGateLock* Key, bool Value)
{
	if (PearlGateLockList.Num() > 0)
	{
		PearlGateLockList[Key] = Value;
	}
	if (Value == true)
	{
		if (CheckAllLockStatus())
		{
			TriggerOpenGate();
		}
	}
}

bool APearlyGate::CheckAllLockStatus()
{
	if (PearlGateLockList.Num() > 0)
	{
		for (auto Lock : PearlGateLockList)
		{
			if (!Lock.Value)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

void APearlyGate::TriggerOpenGate()
{
	OpenGate();
	if (DoorOpenSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DoorOpenSound, GetActorLocation());
	}
	bGateIsOpen = true;
}


