// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "UE_GAS_StudyGameplayAbility.h"
#include "UE_GAS_StudyGameplayAbility_Death.generated.h"

UCLASS(Abstract)
class UE_GAS_STUDY_API UUE_GAS_StudyGameplayAbility_Death : public UUE_GAS_StudyGameplayAbility
{
	GENERATED_BODY()

public:
	UUE_GAS_StudyGameplayAbility_Death(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	                        bool bWasCancelled) override;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void StartDeath();
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void FinishDeath();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Death)
	bool bAutoStartDeath;
};
