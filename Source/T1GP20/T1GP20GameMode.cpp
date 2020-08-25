// Copyright Epic Games, Inc. All Rights Reserved.

#include "T1GP20GameMode.h"
#include "T1GP20Character.h"
#include "UObject/ConstructorHelpers.h"

AT1GP20GameMode::AT1GP20GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
