// Fill out your copyright notice in the Description page of Project Settings.


#include "Interacter.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UInteracter::UInteracter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteracter::BeginPlay()
{
	Super::BeginPlay();

	// ...

	
}


// Called every frame
void UInteracter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor* UInteracter::TriggerInteract(FTransform RayOrigin, FVector ForwardVector)
{
	FVector Start = RayOrigin.GetLocation();
	FVector End = Start + (ForwardVector * ShootingDistance);
	FHitResult Hit;

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility))
	{
		if (Cast<IInteractable>(Hit.GetActor()))
		{
			Cast<IInteractable>(Hit.GetActor())->Execute_Interact(Hit.GetActor());
		}
	}

	return Hit.GetActor();
}







