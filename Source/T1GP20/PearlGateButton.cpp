// Fill out your copyright notice in the Description page of Project Settings.


#include "PearlGateButton.h"

APearlGateButton::APearlGateButton()
{
	PuzzleButton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PuzzleButton"));
	PuzzleButton->SetupAttachment(GetRootComponent());

	RotateDirection = ERotationWays::ERW_Pitch;
	DegreeToRotate = -90.0f;
}

void APearlGateButton::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = ObjectMesh->GetComponentLocation();
	InitialRotation = ObjectMesh->GetComponentRotation();
}

void APearlGateButton::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	UE_LOG(LogTemp, Warning, TEXT("Child"));
}

void APearlGateButton::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	UE_LOG(LogTemp, Warning, TEXT("Child"));

}

//void APearlGateButton::Interact_Implementation()
//{
//	switch (RotateDirection)
//	{
//	case ERotationWays::ERW_Pitch:
//		PuzzleButton->AddLocalRotation(FRotator(DegreeToRotate, 0.0f, 0.0f));
//		break;
//	case ERotationWays::ERW_Yaw:
//		PuzzleButton->AddLocalRotation(FRotator(0.0f, DegreeToRotate, 0.0f));
//		break;
//	case ERotationWays::ERW_Roll:
//		PuzzleButton->AddLocalRotation(FRotator(0.0f, 0.0f, DegreeToRotate));
//		break;
//	case ERotationWays::ERW_Max:
//		break;
//	default:
//		break;
//	}
//}