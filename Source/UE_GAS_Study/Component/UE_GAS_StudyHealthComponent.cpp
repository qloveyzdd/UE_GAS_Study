// Fill out your copyright notice in the Description page of Project Settings.


#include "UE_GAS_StudyHealthComponent.h"

#include "Net/UnrealNetwork.h"
#include "UE_GAS_Study/UE_GAS_StudyGameplayTag.h"
#include "UE_GAS_Study/UE_GAS_StudyLogChannel.h"
#include "UE_GAS_Study/AbilitySystem/UE_GAS_StudyAbilitySystemComponent.h"
#include "UE_GAS_Study/AbilitySystem/Attributes/UE_GAS_StudyCharacterAttributeSet.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_Damage, "Gameplay.Damage");
UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_DamageImmunity, "Gameplay.DamageImmunity");
UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_DamageSelfDestruct, "Gameplay.SelfDestruct");
UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_FellOutOfWorld, "Gameplay.FellOutOfWorld");
UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_Message, "Gameplay.Message");

// Sets default values for this component's properties
UUE_GAS_StudyHealthComponent::UUE_GAS_StudyHealthComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);

	AbilitySystemComponent = nullptr;
	HealthSet = nullptr;
	DeathState = EGAS_StudyDeathState::NotDead;
}

void UUE_GAS_StudyHealthComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UUE_GAS_StudyHealthComponent, DeathState);
}

void UUE_GAS_StudyHealthComponent::OnRep_DeathState(EGAS_StudyDeathState OldState)
{
	const EGAS_StudyDeathState NewDeathState = DeathState;

	DeathState = OldState;

	if (OldState > NewDeathState)
	{
		UE_LOG(LogGAS_Study, Warning, TEXT("[%d]客户端状态大于服务器状态！！！"), (uint8)OldState);
		return;
	}

	if (OldState == EGAS_StudyDeathState::NotDead)
	{
		if (NewDeathState == EGAS_StudyDeathState::DeathStarted)
		{
			StartDeath();
		}
		else if (NewDeathState == EGAS_StudyDeathState::DeathFinished)
		{
			StartDeath();
			FinishDeath();
		}
		else
		{
			UE_LOG(LogGAS_Study, Error, TEXT("[%d]代码错误！！！"), (uint8)OldState);
		}
	}
	else if (OldState == EGAS_StudyDeathState::DeathStarted)
	{
		if (NewDeathState == EGAS_StudyDeathState::DeathFinished)
		{
			FinishDeath();
		}
		else
		{
			UE_LOG(LogGAS_Study, Error, TEXT("[%d]代码错误！！！"), (uint8)OldState);
		}
	}
	ensureMsgf((DeathState==NewDeathState), TEXT("[%d]代码错误！！！"), (uint8)OldState);
}

UUE_GAS_StudyHealthComponent* UUE_GAS_StudyHealthComponent::FindHealthComponent(const AActor* Actor)
{
	return Actor ? Actor->FindComponentByClass<UUE_GAS_StudyHealthComponent>() : nullptr;
}

void UUE_GAS_StudyHealthComponent::InitializeWithAbilitySystem(class UUE_GAS_StudyAbilitySystemComponent* InASC)
{
	AActor* Owner = GetOwner();
	check(Owner);

	if (AbilitySystemComponent)
	{
		UE_LOG(LogGAS_Study, Error, TEXT("[%s]技能组件已初始化！！！"), *GetNameSafe(Owner));
		return;
	}
	AbilitySystemComponent = InASC;
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogGAS_Study, Error, TEXT("[%s]技能组件初始化未成功！！！"), *GetNameSafe(Owner));
		return;
	}

	HealthSet = AbilitySystemComponent->GetSet<UUE_GAS_StudyCharacterAttributeSet>();
	if (!HealthSet)
	{
		UE_LOG(LogGAS_Study, Error, TEXT("[%s]技能属性初始化未成功！！！"), *GetNameSafe(Owner));
		return;
	}

	HealthSet->OnHealthChanged.AddUObject(this, &ThisClass::HandleHealthChanged);
	HealthSet->OnMaxHealthChanged.AddUObject(this, &ThisClass::HandleMaxHealthChanged);
	HealthSet->OnOutOfHealth.AddUObject(this, &ThisClass::HandleOutOfChanged);
	HealthSet->OnManaChanged.AddUObject(this, &ThisClass::HandleManaChanged);
	HealthSet->OnMaxManaChanged.AddUObject(this, &ThisClass::HandleMaxManaChanged);

	AbilitySystemComponent->SetNumericAttributeBase(UUE_GAS_StudyCharacterAttributeSet::GetHealthAttribute(),
	                                                HealthSet->GetMaxHealth());

	ClearGameplayTags();

	OnHealthChanged.Broadcast(this, HealthSet->GetHealth(), HealthSet->GetHealth(), nullptr);
	OnMaxHealthChanged.Broadcast(this, HealthSet->GetMaxHealth(), HealthSet->GetMaxHealth(), nullptr);
}

void UUE_GAS_StudyHealthComponent::UnInitializeWithAbilitySystem(class UUE_GAS_StudyAbilitySystemComponent* InASC)
{
	ClearGameplayTags();

	if (HealthSet)
	{
		HealthSet->OnHealthChanged.RemoveAll(this);
		HealthSet->OnMaxHealthChanged.RemoveAll(this);
		HealthSet->OnOutOfHealth.RemoveAll(this);
		HealthSet->OnManaChanged.RemoveAll(this);
		HealthSet->OnMaxManaChanged.RemoveAll(this);
	}

	HealthSet = nullptr;
	AbilitySystemComponent = nullptr;
}

float UUE_GAS_StudyHealthComponent::GetHealth() const
{
	return HealthSet ? HealthSet->GetHealth() : 0.0f;
}

float UUE_GAS_StudyHealthComponent::GetMaxHealth() const
{
	return HealthSet ? HealthSet->GetMaxHealth() : 0.0f;
}

float UUE_GAS_StudyHealthComponent::GetMana() const
{
	return HealthSet ? HealthSet->GetMana() : 0.0f;
}

float UUE_GAS_StudyHealthComponent::GetMaxMana() const
{
	return HealthSet ? HealthSet->GetMaxMana() : 0.0f;
}

float UUE_GAS_StudyHealthComponent::GetHealthNormalized() const
{
	if (HealthSet)
	{
		const float Health = HealthSet->GetHealth();
		const float MaxHealth = HealthSet->GetMaxHealth();

		return Health > 0.0f ? Health / MaxHealth : 0.0f;
	}
	return 0.0f;
}

float UUE_GAS_StudyHealthComponent::GetManaNormalized() const
{
	if (HealthSet)
	{
		const float Mana = HealthSet->GetMana();
		const float MaxMana = HealthSet->GetMaxMana();

		return MaxMana > 0.0f ? Mana / MaxMana : 0.0f;
	}
	return 0.0f;
}

EGAS_StudyDeathState UUE_GAS_StudyHealthComponent::GetDeathState() const
{
	return DeathState;
}

bool UUE_GAS_StudyHealthComponent::IsDeadOrDying() const
{
	return DeathState > EGAS_StudyDeathState::NotDead;
}

void UUE_GAS_StudyHealthComponent::StartDeath()
{
	if (DeathState != EGAS_StudyDeathState::NotDead)
	{
		return;
	}

	DeathState = EGAS_StudyDeathState::DeathStarted;

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->SetLooseGameplayTagCount(UE_GAS_StudyGameplayTags::Status_Death_Dying, 0);
	}
	AActor* Owner = GetOwner();
	check(Owner);

	OnDeathStarted.Broadcast(Owner);

	Owner->ForceNetUpdate();
}

void UUE_GAS_StudyHealthComponent::FinishDeath()
{
	if (DeathState != EGAS_StudyDeathState::DeathStarted)
	{
		return;
	}

	DeathState = EGAS_StudyDeathState::DeathFinished;

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->SetLooseGameplayTagCount(UE_GAS_StudyGameplayTags::Status_Death_Dead, 0);
	}
	AActor* Owner = GetOwner();
	check(Owner);

	OnDeathFinished.Broadcast(Owner);

	Owner->ForceNetUpdate();
}

void UUE_GAS_StudyHealthComponent::DamageSelfDestroy(bool bFellOutOfWorld)
{
}

void UUE_GAS_StudyHealthComponent::OnUnregister()
{
	UnInitializeWithAbilitySystem(AbilitySystemComponent);

	Super::OnUnregister();
}

void UUE_GAS_StudyHealthComponent::ClearGameplayTags()
{
	if (AbilitySystemComponent)
	{
		// 把某个“松散 GameplayTag”（这里是死亡相关的 Tag）的计数清零，相当于移除这个 Tag 的所有叠加效果。
		AbilitySystemComponent->SetLooseGameplayTagCount(UE_GAS_StudyGameplayTags::Status_Death_Dying, 0);
		AbilitySystemComponent->SetLooseGameplayTagCount(UE_GAS_StudyGameplayTags::Status_Death_Dead, 0);
	}
}

void UUE_GAS_StudyHealthComponent::HandleHealthChanged(AActor* DamageInstigator, AActor* DamageCauser,
                                                       const struct FGameplayEffectSpec* DamageEffectSpec,
                                                       float DamageMagnitude, float OldValue, float NewValue)
{
	OnHealthChanged.Broadcast(this, OldValue, NewValue, DamageInstigator);
}

void UUE_GAS_StudyHealthComponent::HandleMaxHealthChanged(AActor* DamageInstigator, AActor* DamageCauser,
                                                          const struct FGameplayEffectSpec* DamageEffectSpec,
                                                          float DamageMagnitude, float OldValue, float NewValue)
{
	OnMaxHealthChanged.Broadcast(this, OldValue, NewValue, DamageInstigator);
}

void UUE_GAS_StudyHealthComponent::HandleOutOfChanged(AActor* DamageInstigator, AActor* DamageCauser,
                                                      const struct FGameplayEffectSpec* DamageEffectSpec,
                                                      float DamageMagnitude, float OldValue, float NewValue)
{
#if WITH_SERVER_CODE

	if (AbilitySystemComponent && DamageEffectSpec)
	{
		FGameplayEventData Payload;
		Payload.EventTag = UE_GAS_StudyGameplayTags::GameplayEvent_Death;
		Payload.Instigator = DamageInstigator;
		Payload.Target = AbilitySystemComponent->GetAvatarActor();
		Payload.OptionalObject = DamageEffectSpec->Def;
		Payload.ContextHandle = DamageEffectSpec->GetEffectContext();
		Payload.InstigatorTags = *DamageEffectSpec->CapturedSourceTags.GetAggregatedTags();
		Payload.TargetTags = *DamageEffectSpec->CapturedTargetTags.GetAggregatedTags();
		Payload.EventMagnitude = DamageMagnitude;

		FScopedPredictionWindow NewScopedWindow(AbilitySystemComponent, true);
		AbilitySystemComponent->HandleGameplayEvent(Payload.EventTag, &Payload);
	}

#endif
}

void UUE_GAS_StudyHealthComponent::HandleManaChanged(AActor* DamageInstigator, AActor* DamageCauser,
                                                     const struct FGameplayEffectSpec* DamageEffectSpec,
                                                     float DamageMagnitude, float OldValue, float NewValue)
{
	OnManaChanged.Broadcast(this, OldValue, NewValue, DamageInstigator);
}

void UUE_GAS_StudyHealthComponent::HandleMaxManaChanged(AActor* DamageInstigator, AActor* DamageCauser,
                                                        const struct FGameplayEffectSpec* DamageEffectSpec,
                                                        float DamageMagnitude, float OldValue, float NewValue)
{
	OnMaxManaChanged.Broadcast(this, OldValue, NewValue, DamageInstigator);
}
