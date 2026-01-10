// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "UE_GAS_StudyAssetManager.generated.h"

UCLASS(Config = Game)
class UE_GAS_STUDY_API UUE_GAS_StudyAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	UUE_GAS_StudyAssetManager();
	
};
