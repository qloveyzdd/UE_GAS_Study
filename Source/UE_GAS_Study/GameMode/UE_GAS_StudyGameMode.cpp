// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_GAS_StudyGameMode.h"

#include "UE_GAS_StudyGameState.h"
#include "UE_GAS_Study/Character/UE_GAS_StudyCharacter.h"
#include "UE_GAS_Study/Player/UE_GAS_StudyPlayerController.h"
#include "UE_GAS_Study/UI/UE_GAS_StudyHUD.h"

AUE_GAS_StudyGameMode::AUE_GAS_StudyGameMode()
{
	DefaultPawnClass = AUE_GAS_StudyCharacter::StaticClass();
	GameStateClass = AUE_GAS_StudyGameState::StaticClass();
	PlayerControllerClass = AUE_GAS_StudyPlayerController::StaticClass();
	PlayerStateClass = AUE_GAS_StudyPlayerController::StaticClass();
	HUDClass = AUE_GAS_StudyHUD::StaticClass();
}
