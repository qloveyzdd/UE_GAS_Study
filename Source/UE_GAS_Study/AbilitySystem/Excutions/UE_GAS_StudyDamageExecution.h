// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "GameplayEffectExecutionCalculation.h"

#include "UE_GAS_StudyDamageExecution.generated.h"

UCLASS()
class UE_GAS_STUDY_API UUE_GAS_StudyDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UUE_GAS_StudyDamageExecution();

protected:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
