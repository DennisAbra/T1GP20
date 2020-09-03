// Fill out your copyright notice in the Description page of Project Settings.


#include "CryptDoor.h"

// Sets default values
ACryptDoor::ACryptDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACryptDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACryptDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACryptDoor::LibraryPuzzleComplete()
{
	bLibraryComplete = true;
	TryOpenDoor();
}

void ACryptDoor::SacrificialPuzzleComplete()
{
	bSacrificialComplete = true;
	TryOpenDoor();
}

void ACryptDoor::TryOpenDoor()
{
	if (bLibraryComplete && bSacrificialComplete)
	{
		UE_LOG(LogTemp, Warning, TEXT("Crypt door opens"));
		OpenDoor();
	}
}

