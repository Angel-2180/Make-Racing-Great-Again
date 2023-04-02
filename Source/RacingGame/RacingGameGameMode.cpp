// Copyright Epic Games, Inc. All Rights Reserved.

#include "RacingGameGameMode.h"
#include "RacingGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARacingGameGameMode::ARacingGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_Player"));
	if (PlayerPawnBPClass.Class)
		DefaultPawnClass = PlayerPawnBPClass.Class;
}
