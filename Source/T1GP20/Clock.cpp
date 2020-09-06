// Fill out your copyright notice in the Description page of Project Settings.


#include "Clock.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "FirstPersonController.h"

// Sets default values
AClock::AClock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	ClockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ClockMesh"));
	ClockMesh->SetupAttachment(GetRootComponent());

	HourHandParent = CreateDefaultSubobject<USceneComponent>(TEXT("HourHandParent"));
	HourHandParent->SetupAttachment(ClockMesh);

	HourHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HourHandMesh"));
	HourHandMesh->SetupAttachment(HourHandParent);
	
	MinuteHandParent = CreateDefaultSubobject<USceneComponent>(TEXT("MinuteHandParent"));
	MinuteHandParent->SetupAttachment(ClockMesh);

	MinuteHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MinuteHandMesh"));
	MinuteHandMesh->SetupAttachment(MinuteHandParent);

	SecondHandParent = CreateDefaultSubobject<USceneComponent>(TEXT("SecondHandParent"));
	SecondHandParent->SetupAttachment(ClockMesh);

	SecondHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondHandMesh"));
	SecondHandMesh->SetupAttachment(SecondHandParent);

	RotateDirection = ERotateDirection::ERD_Yaw;
	 
	SecondHandRotateDegreePerSec = 6.0f;  
	MinuteHandRotateDegreePerSec = 0.1f; 
	HourHandRotateDegreePerSec = 0.0016666666666667f; 

	MaxSecondToEndTime = 600;
	TimeTickingCounter = 0;

	bShouldTickSound = false;
	TickingSoundVolume = 1.0f;
	bShouldRingBellSound = false;
	BellSoundVolume = 1.0f;
	SecondsToRingBellInterval = 60.0f;
}

// Called when the game starts or when spawned
void AClock::BeginPlay()
{
	Super::BeginPlay();
	
	SetStartTime();
	RingBellCounter = SecondsToRingBellInterval;
	if (Player == nullptr)
	{
		Player = Cast<AFirstPersonController>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	}
}

// Called every frame
void AClock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldRingBellSound && ClockBellSound)
	{
		if (TimeTickingCounter >= RingBellCounter)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ClockBellSound, GetActorLocation(), BellSoundVolume);
			RingBellCounter += SecondsToRingBellInterval;
			BellRing();
			if (Player)
			{
				Player->ShakeItBaby();
			}
		}
	}
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
		SecondHandParent->AddLocalRotation(FRotator(SecondHandRotateDegreePerSec, 0.0f, 0.0f));
		MinuteHandParent->AddLocalRotation(FRotator(MinuteHandRotateDegreePerSec, 0.0f, 0.0f));
		HourHandParent->AddLocalRotation(FRotator(HourHandRotateDegreePerSec, 0.0f, 0.0f));
		break;
	case ERotateDirection::ERD_Yaw:
		SecondHandParent->AddLocalRotation(FRotator(0.0f, SecondHandRotateDegreePerSec, 0.0f));
		MinuteHandParent->AddLocalRotation(FRotator(0.0f, MinuteHandRotateDegreePerSec, 0.0f));
		HourHandParent->AddLocalRotation(FRotator(0.0f, HourHandRotateDegreePerSec, 0.0f));
		break;
	case ERotateDirection::ERD_Roll:
		SecondHandParent->AddLocalRotation(FRotator(0.0f, 0.0f, SecondHandRotateDegreePerSec));
		MinuteHandParent->AddLocalRotation(FRotator(0.0f, 0.0f, MinuteHandRotateDegreePerSec));
		HourHandParent->AddLocalRotation(FRotator(0.0f, 0.0f, HourHandRotateDegreePerSec));
		break;
	case ERotateDirection::ERD_Max:
		break;
	default:
		break;
	}
	if (bShouldTickSound && ClockTickingSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ClockTickingSound, GetActorLocation(), TickingSoundVolume);
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
		HourHandRotation.Pitch = -((float)(StartHour * HourScale) + (float)(StartMinute * HourScale / 60));
		HourHandParent->AddLocalRotation(HourHandRotation);

		MinHandRotation.Pitch = -((float)(StartMinute * MinSacle));
		MinuteHandParent->AddLocalRotation(MinHandRotation);

		break;
	case ERotateDirection::ERD_Yaw:
		HourHandRotation.Yaw = (float)(StartHour * HourScale) + (float)(StartMinute * HourScale / 60);
		HourHandParent->AddLocalRotation(HourHandRotation);

		MinHandRotation.Yaw = (float)(StartMinute * MinSacle);
		MinuteHandParent->AddLocalRotation(MinHandRotation);
		break;
	case ERotateDirection::ERD_Roll:
		HourHandRotation.Roll = (float)(StartHour * HourScale) + (float)(StartMinute * HourScale / 60);
		HourHandParent->AddLocalRotation(HourHandRotation);

		MinHandRotation.Roll = (float)(StartMinute * MinSacle);
		MinuteHandParent->AddLocalRotation(MinHandRotation);
		break;
	case ERotateDirection::ERD_Max:
		break;
	default:
		break;
	}

}





