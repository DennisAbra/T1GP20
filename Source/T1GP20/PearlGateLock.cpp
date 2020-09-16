// Fill out your copyright notice in the Description page of Project Settings.


#include "PearlGateLock.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "PearlyGate.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APearlGateLock::APearlGateLock()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	ParentLock = CreateDefaultSubobject<USceneComponent>(TEXT("ParentLock"));
	ParentLock->SetupAttachment(GetRootComponent());

	LockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LockMesh"));
	LockMesh->SetupAttachment(ParentLock);

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMeshCheck"));
	KeyMesh->SetupAttachment(GetRootComponent());

	SlotRotation = FRotator(0.0f);
	AcceptableRange = 5.0f;
	SelfDestroyDelay = 1.0f;

	bIsDestroyed = false;
	
	UnLockSoundVolume = 1.0f;
	DelayPlaySound = 0.5f;
}

// Called when the game starts or when spawned
void APearlGateLock::BeginPlay()
{
	Super::BeginPlay();
}

void APearlGateLock::RotateLock(FRotator Rotation)
{
	LockMesh->SetRelativeRotation(Rotation);
}

void APearlGateLock::CheckLockRotation()
{
	if (FMath::Abs((SlotRotation.Roll - LockMesh->GetRelativeRotation().Roll) - 360) <= AcceptableRange)
	{
		SnapToRotation();
	}
}

void APearlGateLock::SnapToRotation()
{
	LockMesh->SetRelativeRotation(SlotRotation);
	EmitPuzzleCompleteSignal();
}

void APearlGateLock::EmitPuzzleCompleteSignal()
{
	if (PearlyGate)
	{
		PearlyGate->UpdateGateLockStatus(this, true);
	}
	GetWorldTimerManager().SetTimer(DelayPlaySoundTimerHandle, this, &APearlGateLock::PlayUnLockSound, DelayPlaySound);
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &APearlGateLock::Disappear, SelfDestroyDelay);
}

void APearlGateLock::PlayUnLockSound()
{
	if (UnLockSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, UnLockSound, GetActorLocation(), UnLockSoundVolume);
	}
}

void APearlGateLock::Disappear()
{
	bIsDestroyed = true;
	Destroy();
}


