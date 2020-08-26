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

	bActiveItemCheck = false;
	bActiveWeightCheck = false;

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
	if (TriggerDoor && !TriggerDoor->bIsDoorOpened)
	{
		if (bActiveWeightCheck)
		{
			if (OtherActor && OtherComp)
			{
				float ObjectWeight = OtherComp->GetMass();
				if (ObjectWeight)
				{
					if (ObjectWeight <= MaxWeightToTrigger && ObjectWeight >= MinWeightToTrigger)
					{
						TriggerPass();
					}
				}
			}
		}
		else if (bActiveItemCheck)
		{
			if (OtherActor)
			{
				AItem* ObjectToTest = Cast<AItem>(OtherActor);
				if (ObjectToTest == KeyItem)
				{
					TriggerPass();
				}
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
	if (TriggerDoor)
	{
		TriggerDoor->UpdatePressurePadStatus(this, false);
		TriggerDoor->CloseDoor();
		TriggerDoor->bIsDoorOpened = false;
	}
}

