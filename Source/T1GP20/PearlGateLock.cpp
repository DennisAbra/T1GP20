// Fill out your copyright notice in the Description page of Project Settings.


#include "PearlGateLock.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "PearlyGate.h"

// Sets default values
APearlGateLock::APearlGateLock()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	ParentLock = CreateDefaultSubobject<USceneComponent>(TEXT("ParentLock"));
	ParentLock->SetupAttachment(GetRootComponent());

	LockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LockMesh"));
	LockMesh->SetupAttachment(ParentLock);

	KeyCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("KeyCollisionBox"));
	KeyCollisionBox->SetupAttachment(LockMesh);

	KeyMeshCheck = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMeshCheck"));
	KeyMeshCheck->SetupAttachment(GetRootComponent());

	SlotRotation = FRotator(0.0f);
}

// Called when the game starts or when spawned
void APearlGateLock::BeginPlay()
{
	Super::BeginPlay();
	
	KeyCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APearlGateLock::OnOverlapBegin);
	KeyCollisionBox->OnComponentEndOverlap.AddDynamic(this, &APearlGateLock::OnOverlapEnd);
}

void APearlGateLock::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp == KeyMeshCheck)
	{
		SnapToRotaiton();
	}
}

void APearlGateLock::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp == KeyMeshCheck)
	{
		if (PearlyGate)
		{
			PearlyGate->UpdateGateLockStatus(this, false);
			if (PearlyGate->bGateIsOpen)
			{
				PearlyGate->CloseGate();
				PearlyGate->bGateIsOpen = false;
			}
		}
	}
}

void APearlGateLock::RotateLock(FRotator Rotation)
{
	LockMesh->SetRelativeRotation(Rotation);
}

void APearlGateLock::Disappear()
{
	LockMesh->SetHiddenInGame(true);
	KeyMeshCheck->SetHiddenInGame(true);
}

void APearlGateLock::SnapToRotaiton()
{
	LockMesh->SetRelativeRotation(SlotRotation);

	if (PearlyGate)
	{
		PearlyGate->UpdateGateLockStatus(this, true);
	}
}



