#include "FirstPersonController.h"
#include "GameFramework/CharacterMovementComponent.h"


AFirstPersonController::AFirstPersonController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationYaw = false;
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->AttachTo(RootComponent);

	GetCharacterMovement()->AirControl = AirControl;
	CrouchSpeed = Walkspeed * 0.5;
	Sprintspeed = Walkspeed * 2;
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
	InputComponent->BindAction("Crouch", IE_Pressed, this, &AFirstPersonController::Crouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &AFirstPersonController::StopCrouch);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
<<<<<<< Updated upstream


	
=======
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
			FirstPersonCamera->AddLocalRotation(FRotator(Input, 0, 0));
=======
			if (!bIsSprinting)
			{
				FirstPersonCamera->AddLocalRotation(FRotator(Input * Sensitivity, 0, 0));
			}
			else
			{
				FirstPersonCamera->AddLocalRotation(FRotator(Input * Sensitivity * SprintSlowSensMultiplyer, 0, 0));
			}
>>>>>>> Stashed changes
		}
	}
}

void AFirstPersonController::LookY(float Input)
{
	if (Input)
	{
<<<<<<< Updated upstream
		AddActorLocalRotation(FRotator(0, Input, 0));
=======
		if (!bIsSprinting)
		{
			AddActorLocalRotation(FRotator(0, Input * Sensitivity, 0));
		}
		else
		{
			AddActorLocalRotation(FRotator(0, Input * Sensitivity * SprintSlowSensMultiplyer, 0));
		}
>>>>>>> Stashed changes
	}
}

void AFirstPersonController::Crouch()
{
<<<<<<< Updated upstream
	UE_LOG(LogTemp, Warning, TEXT("Crouchy crouch"));
=======
	bIsCrouching = true;
>>>>>>> Stashed changes
	GetCharacterMovement()->Crouch(true);
	GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
}

void AFirstPersonController::StopCrouch()
{
<<<<<<< Updated upstream
	UE_LOG(LogTemp, Warning, TEXT("Stopped crouching"));
	GetCharacterMovement()->UnCrouch(false);
}
=======
	bIsCrouching = false;
	GetCharacterMovement()->UnCrouch(true);
	GetCharacterMovement()->MaxWalkSpeed = Walkspeed;
}

void AFirstPersonController::Sprint()
{
	bIsSprinting = true;
	if (!bIsCrouching)
	{
		GetCharacterMovement()->MaxWalkSpeed = Sprintspeed;
	}
}

void AFirstPersonController::StopSprint()
{
	bIsSprinting = false;
	if (!bIsCrouching)
	{
		GetCharacterMovement()->MaxWalkSpeed = Walkspeed;
	}	
}
>>>>>>> Stashed changes
