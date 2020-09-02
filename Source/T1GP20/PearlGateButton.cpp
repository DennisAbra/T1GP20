// Fill out your copyright notice in the Description page of Project Settings.


#include "PearlGateButton.h"
#include "FirstPersonController.h"
#include "Kismet/KismetMathLibrary.h"

APearlGateButton::APearlGateButton()
{
	PuzzleParent = CreateDefaultSubobject<USceneComponent>(TEXT("PuzzleParent"));
	PuzzleParent->SetupAttachment(GetRootComponent());

	PuzzleButton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PuzzleButton"));
	PuzzleButton->SetupAttachment(PuzzleParent);


	bMouseLeftClickToggle = false;
	bObjectRotationActivate = false;
	InterpSpeed = 1.0f;

	bActive = false;
}

void APearlGateButton::BeginPlay()
{
	Super::BeginPlay();

	if (Player == nullptr)
	{
		Player = Cast<AFirstPersonController>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	}
	InitialLocation = ObjectMesh->GetComponentLocation();
	InitialRotation = ObjectMesh->GetComponentRotation();
}

void APearlGateButton::Tick(float DeltaTime)
{
	if (bObjectRotationActivate && Player)
	{
		//RotateObject();
		Player->bMouseLook = false;

		float ValueY = (Player->GetInputAxisValue("LookUp"));
		if (ValueY != 0)
		{
			PuzzleButton->AddLocalRotation(FRotator(0.0f, ValueY * InterpSpeed, 0.0f));
		}

	}
}


void APearlGateButton::Interact_Implementation()
{
	if (!bActive)
	{
		return;
	}
	bMouseLeftClickToggle = !bMouseLeftClickToggle;

	if (bMouseLeftClickToggle)
	{
		MouseRedirection();
		SetActivateObjectRotation(true);
	}
	else
	{
		SetActivateObjectRotation(false);
		if (Player)
		{
			Player->bMouseLook = true;
		}
	}
}



void APearlGateButton::SetActivateObjectRotation(bool Active)
{
	bObjectRotationActivate = Active;
}


