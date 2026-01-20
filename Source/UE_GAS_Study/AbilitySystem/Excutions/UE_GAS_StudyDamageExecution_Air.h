// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "GameplayEffectExecutionCalculation.h"

#include "UE_GAS_StudyDamageExecution_Air.generated.h"

UCLASS()
class UE_GAS_STUDY_API UUE_GAS_StudyDamageExecution_Air : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UUE_GAS_StudyDamageExecution_Air();

protected:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
