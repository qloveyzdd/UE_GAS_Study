// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_GAS_StudyGameMode.h"
#include "UE_GAS_StudyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE_GAS_StudyGameMode::AUE_GAS_StudyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
