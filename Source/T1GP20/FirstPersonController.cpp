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
	FirstPersonCamera->AttachTo(RootComponent);

	GetCharacterMovement()->AirControl = AirControl;
	bCanMove = true;
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
	
	/*if (bIsInspectingItem)
	{
		FirstPersonCamera->SetFieldOfView(FMath::Lerp(FirstPersonCamera->FieldOfView, 50.0f, 0.1f));
	}*/

}

// Called to bind functionality to input
void AFirstPersonController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveRight", this, &AFirstPersonController::MoveX);
	InputComponent->BindAxis("MoveForward", this, &AFirstPersonController::MoveY);
	InputComponent->BindAxis("Turn", this, &AFirstPersonController::LookY);
	InputComponent->BindAxis("LookUp", this, &AFirstPersonController::LookX);
	//InputComponent->BindAction("Interact", IE_Pressed, this, &AFirstPersonController::Interact);
	InputComponent->BindAction("Inspect", IE_Pressed, this, &AFirstPersonController::Inspect);
	InputComponent->BindAction("Inspect", IE_Released, this, &AFirstPersonController::StopInspect);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);


	/*InputComponent->BindAction("Crouch", IE_Pressed, this, &AFirstPersonController::Crouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &AFirstPersonController::StopCrouch);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AFirstPersonController::Sprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AFirstPersonController::StopSprint);*/
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
		if (CurrentPitch < MaxLookUpRange && CurrentPitch > -MaxLookDownRange)
		{
			FirstPersonCamera->AddLocalRotation(FRotator(Input * Sensitivity, 0, 0));
		}
	}
}

void AFirstPersonController::LookY(float Input)
{
	if (Input)
	{
		AddActorLocalRotation(FRotator(0, Input * Sensitivity, 0));
	}
}

void AFirstPersonController::Interact()
{

}

void AFirstPersonController::Inspect()
{
	UE_LOG(LogTemp, Warning, TEXT("Inspect mode"));
	if (bIsHoldingItem)
	{

	}

}

void AFirstPersonController::StopInspect()
{

}

//void AFirstPersonController::Crouch()
//{
//	GetCharacterMovement()->Crouch(true);
//}
//
//void AFirstPersonController::StopCrouch()
//{
//	GetCharacterMovement()->UnCrouch(false);
//}
//
//void AFirstPersonController::Sprint()
//{
//	bIsSprinting = true;
//
//}
//
//void AFirstPersonController::StopSprint()
//{
//	UE_LOG(LogTemp, Warning, TEXT("Stopsprint"));
//	bIsSprinting = false;
//}
