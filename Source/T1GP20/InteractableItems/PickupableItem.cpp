// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupableItem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickupableItem::APickupableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickupableItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupableItem::Interact_Implementation()
{

	
}

