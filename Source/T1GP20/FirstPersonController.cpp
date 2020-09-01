#include "FirstPersonController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"


AFirstPersonController::AFirstPersonController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationYaw = false;
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetRootComponent());
	GetCharacterMovement()->AirControl = AirControl;
	bIsInspectingItem = false;
}

// Called when the game starts or when spawned
void AFirstPersonController::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFirstPersonController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFirstPersonController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveRight", this, &AFirstPersonController::MoveX);
	InputComponent->BindAxis("MoveForward", this, &AFirstPersonController::MoveY);
	InputComponent->BindAxis("Turn", this, &AFirstPersonController::LookY);
	InputComponent->BindAxis("LookUp", this, &AFirstPersonController::LookX);

	InputComponent->BindAction("Inspect", IE_Pressed, this, &AFirstPersonController::Inspect);
	InputComponent->BindAction("Inspect", IE_Released, this, &AFirstPersonController::StopInspect);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}


void AFirstPersonController::MoveX(float Input)
{
	if (Input)
	{
		AddMovementInput(GetActorRightVector(), Input);
	}
}

void AFirstPersonController::MoveY(float Input)
{
	if (Input)
	{
		AddMovementInput(GetActorForwardVector(), Input);
	}
}

void AFirstPersonController::LookX(float Input)
{
	Input = bInvertLook ? Input : -Input;

	if (Input)
	{
		float CurrentPitch = FirstPersonCamera->GetRelativeRotation().Pitch + Input;

		if (!bIsInspectingItem && CurrentPitch < MaxLookUpRange && CurrentPitch > -MaxLookDownRange)
		{
			FirstPersonCamera->AddLocalRotation(FRotator(Input * Sensitivity, 0, 0));
		}
		else if (bIsInspectingItem)
		{
			CurrentHeldItem->GetAttachParent()->AddLocalRotation(FRotator(-Input * Sensitivity, 0, 0));
			//CurrentHeldItem->AddLocalRotation(FRotator(0, 0, Input));
			
		}
	}

}

void AFirstPersonController::LookY(float Input)
{
	if (Input)
	{
		if (!bIsInspectingItem)
		{
			AddActorLocalRotation(FRotator(0, Input * Sensitivity, 0));
		}
		else if (bIsInspectingItem)
		{
			CurrentHeldItem->AddLocalRotation(FRotator(0, -Input * Sensitivity, 0)); //
		}
	}
}

void AFirstPersonController::Inspect()
{
	if (CurrentHeldItem != nullptr)
	{
		bIsInspectingItem = true;
		UE_LOG(LogTemp, Warning, TEXT("Inspect"));
	}
}

void AFirstPersonController::StopInspect()
{
	bIsInspectingItem = false;
	UE_LOG(LogTemp, Warning, TEXT("Stop inspect"));
	
}