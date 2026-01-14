// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "GameplayEffectExecutionCalculation.h"

#include "UE_GAS_StudyDamageExcution.generated.h"

UCLASS()
class UE_GAS_STUDY_API UUE_GAS_StudyDamageExcution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UUE_GAS_StudyDamageExcution();

protected:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
