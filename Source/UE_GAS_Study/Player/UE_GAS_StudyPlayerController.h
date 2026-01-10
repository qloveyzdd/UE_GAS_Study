// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "UE_GAS_StudyPlayerController.generated.h"

UCLASS(Config=Game, Meta = (ShortTooltip = "The base player controller class used by this project."))
class UE_GAS_STUDY_API AUE_GAS_StudyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AUE_GAS_StudyPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
