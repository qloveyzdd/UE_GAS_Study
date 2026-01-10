// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UE_GAS_StudyCharacterBase.generated.h"

UCLASS(config=Game)
class UE_GAS_STUDY_API AUE_GAS_StudyCharacterBase : public ACharacter
{
	GENERATED_BODY()
	
public:
	AUE_GAS_StudyCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};