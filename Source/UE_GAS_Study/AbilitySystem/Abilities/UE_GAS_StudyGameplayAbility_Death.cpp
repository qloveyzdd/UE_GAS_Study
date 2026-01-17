#include "UE_GAS_StudyGameplayAbility_Death.h"

#include "UE_GAS_Study/UE_GAS_StudyGameplayTag.h"
#include "UE_GAS_Study/AbilitySystem/UE_GAS_StudyAbilitySystemComponent.h"
#include "UE_GAS_Study/Component/UE_GAS_StudyHealthComponent.h"

UUE_GAS_StudyGameplayAbility_Death::UUE_GAS_StudyGameplayAbility_Death(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//如何实例化
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	//如何执行
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;
	
	bAutoStartDeath = true;

	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		FAbilityTriggerData TriggerData;
		TriggerData.TriggerTag = UE_GAS_StudyGameplayTags::GameplayEvent_Death;
		TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
		AbilityTriggers.Add(TriggerData);
	}
}

void UUE_GAS_StudyGameplayAbility_Death::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                         const FGameplayAbilityActorInfo* ActorInfo,
                                                         const FGameplayAbilityActivationInfo ActivationInfo,
                                                         const FGameplayEventData* TriggerEventData)
{
	check(ActorInfo);
	UUE_GAS_StudyAbilitySystemComponent* ASC = CastChecked<UUE_GAS_StudyAbilitySystemComponent>(ActorInfo->AbilitySystemComponent);
	
	FGameplayTagContainer AbilityTypesToIgnore;
	AbilityTypesToIgnore.AddTag(UE_GAS_StudyGameplayTags::Ability_Behavior_SurvivesDeath);
	
	ASC->CancelAbilities(nullptr,&AbilityTypesToIgnore,this);
	
	SetCanBeCanceled(false);

	if (bAutoStartDeath)
	{
		StartDeath();
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UUE_GAS_StudyGameplayAbility_Death::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                                    const FGameplayAbilityActorInfo* ActorInfo,
                                                    const FGameplayAbilityActivationInfo ActivationInfo,
                                                    bool bReplicateEndAbility, bool bWasCancelled)
{
	check(ActorInfo);
	FinishDeath();
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UUE_GAS_StudyGameplayAbility_Death::StartDeath()
{
	if (UUE_GAS_StudyHealthComponent* HealthComponent = UUE_GAS_StudyHealthComponent::FindHealthComponent(GetAvatarActorFromActorInfo()))
	{
		if (HealthComponent->GetDeathState() == EGAS_StudyDeathState::NotDead)
		{
			HealthComponent->StartDeath();
		}
	}
}

void UUE_GAS_StudyGameplayAbility_Death::FinishDeath()
{
	if (UUE_GAS_StudyHealthComponent* HealthComponent = UUE_GAS_StudyHealthComponent::FindHealthComponent(GetAvatarActorFromActorInfo()))
	{
		if (HealthComponent->GetDeathState() == EGAS_StudyDeathState::NotDead)
		{
			HealthComponent->FinishDeath();
		}
	}
}
