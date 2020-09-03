// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Item.h"
#include "CryptDoor.h"
#include "PearlGateButton.h"

// Sets default values
APressurePad::APressurePad()
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	ScalePad = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ScalePad"));
	ScalePad->SetupAttachment(GetRootComponent());

	bItemCorrect = false;
	bWeightCorrect = false;

	CurrentAllItemsWeight = 0.0f;
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
	//CheckScale(OtherActor, OtherComp);
}

void APressurePad::CheckScale(AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
	if (!bComplete)
		if (CryptDoor && OtherActor)
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
							bComplete = true;
							if (GateButton)
								GateButton->bActive = true;
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
	if (!bComplete)
	if (CryptDoor && OtherActor)
	{
		AItem* Object = Cast<AItem>(OtherActor);
		BackToUnTrigger(Object);
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
	if (CryptDoor && bComplete)
	{
		CryptDoor->LibraryPuzzleComplete();
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

void APressurePad::BackToUnTrigger(AItem* Item)
{
	RaiseScalePad();
	if (ItemOnPadList.Contains(Item))
	{
		CurrentAllItemsWeight -= Item->MassWeight;
		ItemOnPadList.Remove(Item);
		bWeightCorrect = CheckWeight();
	}
	if (Item == KeyItem)
	{
		bItemCorrect = false;
	}

	//if (CryptDoor)
	//{
	//	CryptDoor->UpdatePressurePadStatus(this, false);
	//	CryptDoor->CloseDoor();
	//	CryptDoor->bIsDoorOpened = false;
	//}
}

void APressurePad::CheckItem(AItem* Item)
{
	if (Item == KeyItem)
	{
		bItemCorrect = true;
		if (ActiveStatus == EActiveStatus::EAS_KeyItem)
		{
			TriggerPass();
		}
	}
}


bool APressurePad::CheckWeight()
{
	float weight = 0;
	for (auto Item : ItemOnPadList)
	{
		weight += Item.Value;
	}

	if (weight < MaxWeightToTrigger && weight > MinWeightToTrigger)
	{
		return true;
	}
	else return false;
}

void APressurePad::CheckWeight(AItem* Item)
{
	float ObjectWeight = Item->MassWeight;
	if (ObjectWeight)
	{
		if (!ItemOnPadList.Contains(Item))
		{
			ItemOnPadList.Add(Item, ObjectWeight);
			CurrentAllItemsWeight += ObjectWeight;
		}
		if (CurrentAllItemsWeight <= MaxWeightToTrigger && CurrentAllItemsWeight >= MinWeightToTrigger)
		{
			bWeightCorrect = true;
			if (ActiveStatus == EActiveStatus::EAS_Weight)
				TriggerPass();
		}
	}
}


