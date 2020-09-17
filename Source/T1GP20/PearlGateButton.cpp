// Fill out your copyright notice in the Description page of Project Settings.


#include "PearlGateButton.h"
#include "FirstPersonController.h"
#include "Kismet/KismetMathLibrary.h"
#include "PearlGateLock.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"

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

	FaceDirection = EFaceDirection::EFD_Front;

	InterpSpeed = 1.0f;
	AcceptableRange = 0.5f;

	bActive = false;

	ActivateSoundVolume = 1.0f;
	RollingSoundVolume = 1.0f;
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
		PuzzleButton->SetRelativeRotation(PearlGateLock->LockMesh->GetRelativeRotation());
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
		// Rotate object with locked camera view
		/*Player->bMouseLook = false;

		float ValueY = (Player->GetInputAxisValue("LookUp"));
		if (ValueY != 0)
		{
			PuzzleButton->AddLocalRotation(FRotator(0.0f, (ValueY * InterpSpeed), 0.0f));
			if (RollingSound)
			{
				if (!PuzzleAudioComponent->IsPlaying())
				{
					PuzzleAudioComponent->SetSound(RollingSound);
					PuzzleAudioComponent->SetVolumeMultiplier(RollingSoundVolume);
					PuzzleAudioComponent->Play(0.0f);
				}
				else if (PuzzleAudioComponent->bIsPaused)
				{
					PuzzleAudioComponent->SetPaused(false);
				}
			}
			EmitRotationSignal();
		}
		else
		{
			if (PuzzleAudioComponent->IsPlaying())
			{
				PuzzleAudioComponent->SetPaused(true);
			}
		}*/
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
		InteractWhenNotActivate();
		return;
	}
	if (PearlGateLock && PearlGateLock->bIsDestroyed)
	{
		SetActivateObjectRotation(false);
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
	SetActivateObjectRotation(true);
}

void APearlGateButton::FinishInteract()
{
	SetActivateObjectRotation(false);
	IsNotInteracting();

	EmitRotationSignal();
	//if ((PuzzleButton->GetRelativeRotation().Vector() - SlotRotation.Vector()).Size() <= AcceptableRange)
	if (FMath::Abs((SlotRotation.Roll - PuzzleButton->GetRelativeRotation().Roll) - 360) <= AcceptableRange)
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

void APearlGateButton::SetPuzzleActivate(bool Value)
{
	bActive = Value;
	if (bActive)
	{
		if (ActivatePuzzleSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ActivatePuzzleSound, GetActorLocation(), ActivateSoundVolume);
		}
	}
}

int32 APearlGateButton::GetRotationIncrement(EFaceDirection Direction, FVector HitLocation, FVector2D MouseInputValue)
{
	if (HitLocation.X == 0 && HitLocation.Z == 0 && HitLocation.Y == 0)
	{
		return 0;
	}
	float HorizontalPlace = HitLocation.X;

	switch (Direction)
	{
	case EFaceDirection::EFD_Rright:
		HorizontalPlace = HitLocation.Y;
		break;
	case EFaceDirection::EFD_Left:
		HorizontalPlace = HitLocation.Y * -1;
		break;
	case EFaceDirection::EFD_Back:
		HorizontalPlace *= -1;
		break;
	}

	// Diagonals movement
	if (MouseInputValue.X > 0 && MouseInputValue.Y > 0)
	{
		if (HorizontalPlace < 0 && HitLocation.Z > 0)
		{
			return 1;
		}
		if (HorizontalPlace > 0 && HitLocation.Z < 0)
		{
			return -1;
		}
		return 0;
	}
	if (MouseInputValue.X > 0 && MouseInputValue.Y < 0)
	{
		if (HorizontalPlace > 0 && HitLocation.Z > 0)
		{
			return 1;
		}
		if (HorizontalPlace < 0 && HitLocation.Z < 0)
		{
			return -1;
		}
		return 0;
	}
	if (MouseInputValue.X < 0 && MouseInputValue.Y < 0)
	{
		if (HorizontalPlace < 0 && HitLocation.Z > 0)
		{
			return -1;
		}
		if (HorizontalPlace > 0 && HitLocation.Z < 0)
		{
			return 1;
		}
		return 0;
	}
	if (MouseInputValue.X < 0 && MouseInputValue.Y > 0)
	{
		if (HorizontalPlace > 0 && HitLocation.Z > 0)
		{
			return -1;
		}
		if (HorizontalPlace < 0 && HitLocation.Z < 0)
		{
			return 1;
		}
		return 0;
	}
	// Straights movement
	if (MouseInputValue.X > 0 && MouseInputValue.Y == 0)
	{
		if (HitLocation.Z > 0)
		{
			return 1;
		}
		if (HitLocation.Z < 0)
		{
			return -1;
		}
		return 0;
	}
	if (MouseInputValue.X < 0 && MouseInputValue.Y == 0)
	{
		if (HitLocation.Z > 0)
		{
			return -1;
		}
		if (HitLocation.Z < 0)
		{
			return 1;
		}
		return 0;
	}
	if (MouseInputValue.X == 0 && MouseInputValue.Y > 0)
	{
		if (HorizontalPlace < 0)
		{
			return 1;
		}
		if (HorizontalPlace > 0)
		{
			return -1;
		}
		return 0;
	}
	if (MouseInputValue.X == 0 && MouseInputValue.Y < 0)
	{
		if (HorizontalPlace < 0)
		{
			return -1;
		}
		if (HorizontalPlace > 0)
		{
			return 1;
		}
		return 0;
	}
	return 0;
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

