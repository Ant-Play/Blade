// Copyright Epic Games, Inc. All Rights Reserved.

#include "BladeGameMode.h"
#include "BladeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABladeGameMode::ABladeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
