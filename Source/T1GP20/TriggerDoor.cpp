// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerDoor.h"
#include "Components/StaticMeshComponent.h"
#include "PressurePad.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ATriggerDoor::ATriggerDoor()
{
	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh"));
	ObjectMesh->SetupAttachment(GetRootComponent());

	bIsDoorOpened = false;
}

// Called when the game starts or when spawned
void ATriggerDoor::BeginPlay()
{
	Super::BeginPlay();
	
	InitialDoorLocation = ObjectMesh->GetComponentLocation();
}


void ATriggerDoor::UpdateDoorLocation(FVector Location)
{
	FVector NewLocation = InitialDoorLocation;
	NewLocation += Location;
	ObjectMesh->SetWorldLocation(NewLocation);
}

void ATriggerDoor::UpdatePressurePadStatus(APressurePad* Key, bool Value)
{
	if (PressurePadList.Num() > 0)
	{
		if (PressurePadList.Contains(Key))
		{
			PressurePadList[Key] = Value;
		}
		if (Value == true)
		{
			if (CheckAllPressurePadsValue())
			{
				TriggerOpenDoor();
			}
		}
	}
}

bool ATriggerDoor::CheckAllPressurePadsValue()
{
	if (PressurePadList.Num() > 0)
	{
		for (auto Pad : PressurePadList)
		{
			if (!Pad.Value)
				return false;
		}
		return true;
	}
	return false;
}

void ATriggerDoor::TriggerOpenDoor()
{
	OpenDoor();
	if (TriggerSound)
	{
		UGameplayStatics::PlaySound2D(this, TriggerSound);
	}
	bIsDoorOpened = true;
}


