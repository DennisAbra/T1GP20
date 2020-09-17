// Fill out your copyright notice in the Description page of Project Settings.


#include "JigsawPieceComponent.h"

// Sets default values for this component's properties
UJigsawPieceComponent::UJigsawPieceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UJigsawPieceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UJigsawPieceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UJigsawPieceComponent::TestPosition(FTransform CurrentTransform)
{
	if (FVector::Dist(FinalPosition, CurrentTransform.GetLocation()) < PositionMarginal)
	{
		if (FinalRotation.Equals(CurrentTransform.GetRotation().Rotator(), RotationMarginal) || bShouldIgnoreRotation)
		{
			return true;
		}
		return false;
	}
	return false;
}

void UJigsawPieceComponent::SetFinalTransform(FTransform FinalTransform)
{
	FinalPosition = FinalTransform.GetLocation();
	FinalRotation = FinalTransform.GetRotation().Rotator();
}

void UJigsawPieceComponent::SnapIntoPlace(UStaticMeshComponent* MeshToMove)
{
	MeshToMove->SetWorldLocation(FinalPosition);
	MeshToMove->SetWorldRotation(FinalRotation);
	//GetOwner()->SetActorLocation(FinalPosition);
	//GetOwner()->SetActorRotation(FinalRotation.Quaternion());
}

FTransform UJigsawPieceComponent::GetFinalTransform()
{
	FTransform Final;
	Final.SetLocation(FinalPosition);
	Final.SetRotation(FinalRotation.Quaternion());
	return Final;
}

