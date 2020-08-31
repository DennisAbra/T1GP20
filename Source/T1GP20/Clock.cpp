// Fill out your copyright notice in the Description page of Project Settings.


#include "Clock.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

// Sets default values
AClock::AClock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	ClockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ClockMesh"));
	ClockMesh->SetupAttachment(GetRootComponent());

	HourHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HourHandMesh"));
	HourHandMesh->SetupAttachment(ClockMesh);
	
	MinuteHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MinuteHandMesh"));
	MinuteHandMesh->SetupAttachment(ClockMesh);

	SecondHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondHandMesh"));
	SecondHandMesh->SetupAttachment(ClockMesh);

	RotateDirection = ERotateDirection::ERD_Yaw;
	 
	SecondHandRotateDegreePerSec = 6.0f;  
	MinuteHandRotateDegreePerSec = 0.1f; 
	HourHandRotateDegreePerSec = 0.0016666666666667f; 

	MaxSecondToEndTime = 600;
	TimeTickingCounter = 0;
}

// Called when the game starts or when spawned
void AClock::BeginPlay()
{
	Super::BeginPlay();
	
	SetStartTime();

}

// Called every frame
void AClock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TimeTickingCounter >= MaxSecondToEndTime)
	{
		TimesUp();
	}
}

void AClock::StartClockTicking(ERotateDirection Direction)
{
	switch (Direction)
	{
	case ERotateDirection::ERD_Pitch:
		SecondHandMesh->AddLocalRotation(FRotator(-SecondHandRotateDegreePerSec, 0.0f, 0.0f));
		MinuteHandMesh->AddLocalRotation(FRotator(-MinuteHandRotateDegreePerSec, 0.0f, 0.0f));
		HourHandMesh->AddLocalRotation(FRotator(-HourHandRotateDegreePerSec, 0.0f, 0.0f));
		break;
	case ERotateDirection::ERD_Yaw:
		SecondHandMesh->AddLocalRotation(FRotator(0.0f, SecondHandRotateDegreePerSec, 0.0f));
		MinuteHandMesh->AddLocalRotation(FRotator(0.0f, MinuteHandRotateDegreePerSec, 0.0f));
		HourHandMesh->AddLocalRotation(FRotator(0.0f, HourHandRotateDegreePerSec, 0.0f));
		break;
	case ERotateDirection::ERD_Roll:
		SecondHandMesh->AddLocalRotation(FRotator(0.0f, 0.0f, SecondHandRotateDegreePerSec));
		MinuteHandMesh->AddLocalRotation(FRotator(0.0f, 0.0f, MinuteHandRotateDegreePerSec));
		HourHandMesh->AddLocalRotation(FRotator(0.0f, 0.0f, HourHandRotateDegreePerSec));
		break;
	case ERotateDirection::ERD_Max:
		break;
	default:
		break;
	}
	TimeTickingCounter++;
}

void AClock::SetStartTime()
{
	int32 HourScale = 360 / 12;
	int32 MinSacle = 360 / 60;

	FRotator HourHandRotation = HourHandMesh->GetRelativeRotation();
	FRotator MinHandRotation = MinuteHandMesh->GetRelativeRotation();

	switch (RotateDirection)
	{
	case ERotateDirection::ERD_Pitch:
		HourHandRotation.Pitch = (float)(StartHour * HourScale) + (float)(StartMinute * HourScale / 60);
		HourHandMesh->SetRelativeRotation(HourHandRotation);

		MinHandRotation.Pitch = (float)(StartMinute * MinSacle);
		MinuteHandMesh->SetRelativeRotation(MinHandRotation);

		break;
	case ERotateDirection::ERD_Yaw:
		HourHandRotation.Yaw = (float)(StartHour * HourScale) + (float)(StartMinute * HourScale / 60);
		HourHandMesh->SetRelativeRotation(HourHandRotation);

		MinHandRotation.Yaw = (float)(StartMinute * MinSacle);
		MinuteHandMesh->SetRelativeRotation(MinHandRotation);
		break;
	case ERotateDirection::ERD_Roll:
		HourHandRotation.Roll = (float)(StartHour * HourScale) + (float)(StartMinute * HourScale / 60);
		HourHandMesh->SetRelativeRotation(HourHandRotation);

		MinHandRotation.Roll = (float)(StartMinute * MinSacle);
		MinuteHandMesh->SetRelativeRotation(MinHandRotation);

		break;
	case ERotateDirection::ERD_Max:
		break;
	default:
		break;
	}

}





