// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Item.h"
#include "TriggerDoor.h"

// Sets default values
APressurePad::APressurePad()
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	ScalePad = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ScalePad"));
	ScalePad->SetupAttachment(GetRootComponent());

	bItemCorrect = false;
	bWeightCorrect = false;
}

// Called when the game starts or when spawned
void APressurePad::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APressurePad::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APressurePad::OnOverlapEnd);

	InitialScalePadLocation = ScalePad->GetComponentLocation();
}

void APressurePad::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (TriggerDoor && !TriggerDoor->bIsDoorOpened && OtherActor)
	{
		AItem* Object = Cast<AItem>(OtherActor);
		if (Object)
		{
			switch (ActiveStatus)
			{
			case EActiveStatus::EAS_Weight:
				if (OtherComp)
				{
					CheckWeight(Object);
				}
				break;
			case EActiveStatus::EAS_KeyItem:
				if (OtherActor)
				{
					CheckItem(Object);
				}
				break;
			case EActiveStatus::EAS_Both:
				if (OtherActor && OtherComp)
				{
					if (!bItemCorrect)
					{
						CheckItem(Object);
					}
					if (!bWeightCorrect)
					{
						CheckWeight(Object);
					}
					if (bItemCorrect && bWeightCorrect)
					{
						TriggerPass();
					}
				}
				break;
			case EActiveStatus::EAS_MAX:
				break;
			default:
				break;
			}
		}
	}
}


void APressurePad::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (TriggerDoor && TriggerDoor->bIsDoorOpened)
	{
		if (OtherActor)
		{
			BackToUnTrigger();
		}
	}
}


void APressurePad::UpdateScalePadLocation(FVector Location)
{
	FVector NewLocation = InitialScalePadLocation;
	NewLocation += Location;
	ScalePad->SetWorldLocation(NewLocation);
}

void APressurePad::TriggerPass()
{
	if (TriggerDoor)
	{
		TriggerDoor->UpdatePressurePadStatus(this, true);
	}

	LowerScalePad();
	if (PassEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PassEffect, GetActorLocation(), FRotator(0.f), true);
	}
	if (PassSound)
	{
		UGameplayStatics::PlaySound2D(this, PassSound);
	}
}

void APressurePad::BackToUnTrigger()
{
	RaiseScalePad();
	bItemCorrect = false;
	bWeightCorrect = false;
	if (TriggerDoor)
	{
		TriggerDoor->UpdatePressurePadStatus(this, false);
		TriggerDoor->CloseDoor();
		TriggerDoor->bIsDoorOpened = false;
	}
}

void APressurePad::CheckItem(AItem* Item)
{
	if (Item== KeyItem)
	{
		bItemCorrect = true;
		if (ActiveStatus == EActiveStatus::EAS_KeyItem)
		TriggerPass();
	}
}

void APressurePad::CheckWeight(AItem* Item)
{
	float ObjectWeight = Item->MassWeight;
	if (ObjectWeight)
	{
		if (ObjectWeight <= MaxWeightToTrigger && ObjectWeight >= MinWeightToTrigger)
		{
			bWeightCorrect = true;
			if (ActiveStatus == EActiveStatus::EAS_Weight)
			TriggerPass();
		}
	}
}

