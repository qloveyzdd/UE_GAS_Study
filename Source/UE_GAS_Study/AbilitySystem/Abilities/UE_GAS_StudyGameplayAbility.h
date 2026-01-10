// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Abilities/GameplayAbility.h"
#include "UE_GAS_StudyGameplayAbility.generated.h"

UCLASS(Abstract, HideCategories=(Input), meta=(ShortTooltip = "The base gameplay ability class used by this project"))
class UE_GAS_STUDY_API UUE_GAS_StudyGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UUE_GAS_StudyGameplayAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	class UUE_GAS_StudyAbilitySystemComponent* GetGas_StudyAbilitySystemComponentFromActorInfo() const;
	class AUE_GAS_StudyPlayerController* GetGas_StudyPlayerControllerFromActorInfo() const;
	class AController* GetGas_StudyControllerFromActorInfo() const;
	class AUE_GAS_StudyCharacterBase* GetGas_StudyCharacterFromActorInfo() const;
};
