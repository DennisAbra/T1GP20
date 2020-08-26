// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APressurePad::APressurePad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	ScalePad = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ScalePad"));
	ScalePad->SetupAttachment(GetRootComponent());

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(GetRootComponent());

	IsDoorOpened = false;
}

// Called when the game starts or when spawned
void APressurePad::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APressurePad::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APressurePad::OnOverlapEnd);

	InitialDoorLocation = Door->GetComponentLocation();
}

// Called every frame
void APressurePad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APressurePad::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("On"));
	if (OtherActor && OtherComp)
	{
		float ObjectWeight = OtherComp->GetMass();
		if (ObjectWeight <= MaxWeightToTrigger && ObjectWeight >= MinWeightToTrigger)
		{
			LowerScalePad();
			OpenDoor();
			if (PassEffect)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PassEffect, GetActorLocation(), FRotator(0.f), true);
			}
			if (PassSound)
			{
				UGameplayStatics::PlaySound2D(this, PassSound);
			}
			IsDoorOpened = true;
		}
	}
}

void APressurePad::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Off"));
	if (IsDoorOpened)
	{
		if (OtherActor)
		{
			CloseDoor();
		}
	}
}

void APressurePad::UpdateDoorLocation(FVector Location)
{
	FVector NewLocation = InitialDoorLocation;
	NewLocation += Location;
	Door->SetWorldLocation(NewLocation);
}

