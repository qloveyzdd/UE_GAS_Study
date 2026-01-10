#include "UE_GAS_StudyGameplayAbility_Jump.h"

#include "UE_GAS_Study/Character/UE_GAS_StudyCharacterBase.h"

UUE_GAS_StudyGameplayAbility_Jump::UUE_GAS_StudyGameplayAbility_Jump(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//如何实例化
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	//如何执行
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

bool UUE_GAS_StudyGameplayAbility_Jump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                           const FGameplayAbilityActorInfo* ActorInfo,
                                                           const FGameplayTagContainer* SourceTags,
                                                           const FGameplayTagContainer* TargetTags,
                                                           FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!ActorInfo || !ActorInfo->AvatarActor.IsValid())
	{
		return false;
	}
	const AUE_GAS_StudyCharacterBase* Gas_StudyCharacter = Cast<AUE_GAS_StudyCharacterBase>(
		ActorInfo->AvatarActor.Get());
	if (!Gas_StudyCharacter || !Gas_StudyCharacter->CanJump())
	{
		return false;
	}
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	return true;
}

void UUE_GAS_StudyGameplayAbility_Jump::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                                   const FGameplayAbilityActorInfo* ActorInfo,
                                                   const FGameplayAbilityActivationInfo ActivationInfo,
                                                   bool bReplicateEndAbility, bool bWasCancelled)
{
	CharacterJumpStop();
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UUE_GAS_StudyGameplayAbility_Jump::CharacterJumpStart()
{
	if (AUE_GAS_StudyCharacterBase* Gas_StudyCharacter = GetGas_StudyCharacterFromActorInfo())
	{
		if (Gas_StudyCharacter->IsLocallyControlled()&&!Gas_StudyCharacter->bPressedJump)
		{
			Gas_StudyCharacter->UnCrouch();
			Gas_StudyCharacter->Jump();
		}
	}
}

void UUE_GAS_StudyGameplayAbility_Jump::CharacterJumpStop()
{
	if (AUE_GAS_StudyCharacterBase* Gas_StudyCharacter = GetGas_StudyCharacterFromActorInfo())
	{
		if (Gas_StudyCharacter->IsLocallyControlled()&&!Gas_StudyCharacter->bPressedJump)
		{
			Gas_StudyCharacter->StopJumping();
		}
	}
}
