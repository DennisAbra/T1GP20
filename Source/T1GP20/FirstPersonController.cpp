#include "GameFramework/CharacterMovementComponent.h"
#include "FirstPersonController.h"


AFirstPersonController::AFirstPersonController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationYaw = false;
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->AttachTo(RootComponent);

	GetCharacterMovement()->AirControl = AirControl;
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
	if (!bInvertLook)
	{
		Input = -Input;
	}

	if (Input)
	{
		float CurrentPitch = FirstPersonCamera->GetRelativeRotation().Pitch + Input;
		if (CurrentPitch < MaxLookRange && CurrentPitch > -MaxLookRange)
		{
			FirstPersonCamera->AddLocalRotation(FRotator(Input, 0, 0));
		}
	}
}

void AFirstPersonController::LookY(float Input)
{
	if (Input)
	{
		AddActorLocalRotation(FRotator(0, Input, 0));
	}
}
