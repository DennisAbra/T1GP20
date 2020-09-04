// Fill out your copyright notice in the Description page of Project Settings.


#include "PearlGateButton.h"
#include "FirstPersonController.h"
#include "Kismet/KismetMathLibrary.h"
#include "PearlGateLock.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

APearlGateButton::APearlGateButton()
{
	PuzzleParent = CreateDefaultSubobject<USceneComponent>(TEXT("PuzzleParent"));
	PuzzleParent->SetupAttachment(GetRootComponent());

	PuzzleButton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PuzzleButton"));
	PuzzleButton->SetupAttachment(PuzzleParent);

	SlotRotation = FRotator(0.0f);
	bOnOverlapping = false;
	bMouseLeftClickToggle = false;
	bObjectRotationActivate = false;

	InterpSpeed = 1.0f;
	AcceptableRange = 0.5f;

	bActive = false;

	ActivateSoundVolume = 1.0f;
	CorrectSoundVolume = 1.0f;

	bHasPlayedCorrectSound = false;
}

void APearlGateButton::BeginPlay()
{
	Super::BeginPlay();

	PuzzleButton->OnComponentBeginOverlap.AddDynamic(this, &APearlGateButton::OnOverlapBegin);
	PuzzleButton->OnComponentEndOverlap.AddDynamic(this, &APearlGateButton::OnOverlapEnd);

	if (PearlGateLock)
	{
		SlotRotation = PearlGateLock->SlotRotation;
		AcceptableRange = PearlGateLock->AcceptableRange;
	}
	if (Player == nullptr)
	{
		Player = Cast<AFirstPersonController>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	}
}

void APearlGateButton::Tick(float DeltaTime)
{
	if (bObjectRotationActivate && Player)
	{
		RotateObject();
		Player->bMouseLook = false;

		float ValueY = (Player->GetInputAxisValue("LookUp"));
		if (ValueY != 0)
		{
			PuzzleButton->AddLocalRotation(FRotator(0.0f, (ValueY * InterpSpeed), 0.0f));
			EmitRotationSignal();
		}
	}
}

void APearlGateButton::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PearlGateLock && PearlGateLock->bIsDestroyed)
	{
		return;
	}
	if (OtherActor == Player)
	{
		bOnOverlapping = true;
	}
}

void APearlGateButton::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (PearlGateLock && PearlGateLock->bIsDestroyed)
	{
		return;
	}
	if (OtherActor == Player)
	{
		bOnOverlapping = false;
		bMouseLeftClickToggle = false;
		Player->bMouseLook = true;
		FinishInteract();
	}
}

void APearlGateButton::Interact_Implementation()
{
	if (!bActive)
	{
		return;
	}
	if (PearlGateLock && PearlGateLock->bIsDestroyed)
	{
		return;
	}
	if (bOnOverlapping)
	{
		bMouseLeftClickToggle = !bMouseLeftClickToggle;

		if (bMouseLeftClickToggle)
		{
			StartInteract();
		}
		else
		{
			FinishInteract();
			if (Player)
			{
				Player->bMouseLook = true;
			}
		}
	}
}

void APearlGateButton::StartInteract()
{
	MouseRedirection();
	SetActivateObjectRotation(true);
}

void APearlGateButton::FinishInteract()
{
	SetActivateObjectRotation(false);
	EmitRotationSignal();
	if (((PuzzleButton->GetRelativeRotation().Vector() - SlotRotation.Vector()).Size() <= AcceptableRange))
	{
		PuzzleButton->SetRelativeRotation(SlotRotation);
		if (PuzzleCorrectSound && !bHasPlayedCorrectSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, PuzzleCorrectSound, GetActorLocation(), CorrectSoundVolume);
			bHasPlayedCorrectSound = true;
		}
	}
	if (PearlGateLock)
	{
		PearlGateLock->CheckLockRotation();
	}
}

void APearlGateButton::SetPuzzleActivate()
{
	bActive = true;
	if (ActivatePuzzleSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ActivatePuzzleSound, GetActorLocation(), ActivateSoundVolume);
	}
}

void APearlGateButton::SetActivateObjectRotation(bool Active)
{
	bObjectRotationActivate = Active;
}


void APearlGateButton::EmitRotationSignal()
{
	if (PearlGateLock)
	{
		PearlGateLock->RotateLock(PuzzleButton->GetRelativeRotation());
	}
}


