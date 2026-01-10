// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "UE_GAS_StudyGameplayAbility.h"
#include "UE_GAS_StudyGameplayAbility_Jump.generated.h"

UCLASS(Abstract)
class UE_GAS_STUDY_API UUE_GAS_StudyGameplayAbility_Jump : public UUE_GAS_StudyGameplayAbility
{
	GENERATED_BODY()

public:
	UUE_GAS_StudyGameplayAbility_Jump(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                                const FGameplayTagContainer* SourceTags = nullptr,
	                                const FGameplayTagContainer* TargetTags = nullptr,
	                                FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	                        bool bWasCancelled) override;
	
	UFUNCTION(BlueprintCallable,Category="Jump|Ability")
	void CharacterJumpStart();
	UFUNCTION(BlueprintCallable,Category="Jump|Ability")
	void CharacterJumpStop();
};
