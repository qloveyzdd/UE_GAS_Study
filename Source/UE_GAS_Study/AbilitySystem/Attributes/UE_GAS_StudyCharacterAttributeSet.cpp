#include "UE_GAS_StudyCharacterAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "UE_GAS_Study/AbilitySystem/UE_GAS_StudyAbilitySystemComponent.h"

UUE_GAS_StudyCharacterAttributeSet::UUE_GAS_StudyCharacterAttributeSet()
	: Health(100.0f), MaxHealth(100.0f), Mana(80.0f), MaxMana(80.0f),
	  Stamina(50.0f), MaxStamina(50.0f), Attack(10.0f),
	  Defense(2.0f), Exp(0.0f), MaxExp(120.0f)
{
	bOutOfHealth = false;

	MaxHealthBeforeAttributeChange = 0.0f;
	HealthBeforeAttributeChange = 0.0f;
}

void UUE_GAS_StudyCharacterAttributeSet::GetLifetimeReplicatedProps(
	TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UUE_GAS_StudyCharacterAttributeSet, Damage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUE_GAS_StudyCharacterAttributeSet, Level, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUE_GAS_StudyCharacterAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUE_GAS_StudyCharacterAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUE_GAS_StudyCharacterAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUE_GAS_StudyCharacterAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUE_GAS_StudyCharacterAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUE_GAS_StudyCharacterAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUE_GAS_StudyCharacterAttributeSet, Attack, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUE_GAS_StudyCharacterAttributeSet, Defense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUE_GAS_StudyCharacterAttributeSet, Exp, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUE_GAS_StudyCharacterAttributeSet, MaxExp, COND_None, REPNOTIFY_Always);
}


bool UUE_GAS_StudyCharacterAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
	Super::PreGameplayEffectExecute(Data);

	HealthBeforeAttributeChange = GetHealth();
	MaxHealthBeforeAttributeChange = GetMaxHealth();

	return true;
}

void UUE_GAS_StudyCharacterAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();

	AActor* Instigator = EffectContext.GetOriginalInstigator();
	AActor* Causer = EffectContext.GetEffectCauser();

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth() - GetDamage(), 0.0f, GetMaxHealth()));
		SetDamage(0.0f);
	}
	else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetMaxHealthAttribute())
	{
		OnMaxHealthChanged.Broadcast(Instigator, Causer, &Data.EffectSpec, Data.EvaluatedData.Magnitude,
		                             MaxHealthBeforeAttributeChange, GetMaxHealth());
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}
	else if (Data.EvaluatedData.Attribute == GetMaxManaAttribute())
	{
		OnMaxManaChanged.Broadcast(Instigator, Causer, &Data.EffectSpec, Data.EvaluatedData.Magnitude,
		                           MaxHealthBeforeAttributeChange, GetMaxHealth());
	}

	if (GetHealth() != HealthBeforeAttributeChange)
	{
		OnHealthChanged.Broadcast(Instigator, Causer, &Data.EffectSpec, Data.EvaluatedData.Magnitude,
		                          HealthBeforeAttributeChange, GetHealth());
	}

	if (GetHealth() <= 0.0f && !bOutOfHealth)
	{
		OnOutOfHealth.Broadcast(Instigator, Causer, &Data.EffectSpec, Data.EvaluatedData.Magnitude,
		                        HealthBeforeAttributeChange, GetHealth());
	}

	bOutOfHealth = GetHealth() <= 0.0f;
}

void UUE_GAS_StudyCharacterAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute,
                                                                float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
}

void UUE_GAS_StudyCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UUE_GAS_StudyCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue,
                                                             float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		if (GetHealth() > NewValue)
		{
			UUE_GAS_StudyAbilitySystemComponent* ASC = GetGASStudyAbilitySystemComponent();
			check(ASC);

			ASC->ApplyModToAttribute(GetHealthAttribute(), EGameplayModOp::Override, NewValue);
		}
	}

	if (bOutOfHealth && GetHealth() > 0.0f)
	{
		bOutOfHealth = false;
	}
}

void UUE_GAS_StudyCharacterAttributeSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	else if (Attribute == GetMaxHealthAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.0f);
	}
}

void UUE_GAS_StudyCharacterAttributeSet::OnRep_Damage(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUE_GAS_StudyCharacterAttributeSet, Damage, OldValue);
}

void UUE_GAS_StudyCharacterAttributeSet::OnRep_Level(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUE_GAS_StudyCharacterAttributeSet, Level, OldValue);
}

void UUE_GAS_StudyCharacterAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUE_GAS_StudyCharacterAttributeSet, Health, OldValue);

	const float CurrentHealth = GetHealth();
	const float EstimatedMagnitude = CurrentHealth - OldValue.GetCurrentValue();
	OnHealthChanged.Broadcast(nullptr, nullptr, nullptr, EstimatedMagnitude, OldValue.GetCurrentValue(), CurrentHealth);
	if (!bOutOfHealth && CurrentHealth <= 0.0f)
	{
		OnOutOfHealth.Broadcast(nullptr, nullptr, nullptr, EstimatedMagnitude, OldValue.GetCurrentValue(),
		                        CurrentHealth);
	}
	bOutOfHealth = GetHealth() <= 0.0f;
}

void UUE_GAS_StudyCharacterAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUE_GAS_StudyCharacterAttributeSet, MaxHealth, OldValue);
	
	OnHealthChanged.Broadcast(nullptr,nullptr,nullptr,GetMaxHealth()-OldValue.GetCurrentValue(),OldValue.GetCurrentValue(),GetMaxHealth());
}

void UUE_GAS_StudyCharacterAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUE_GAS_StudyCharacterAttributeSet, Mana, OldValue);
	
	const float CurrentMana = GetMana();
	const float EstimatedMagnitude = CurrentMana - OldValue.GetCurrentValue();
	OnManaChanged.Broadcast(nullptr, nullptr, nullptr, EstimatedMagnitude, OldValue.GetCurrentValue(), CurrentMana);
}

void UUE_GAS_StudyCharacterAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUE_GAS_StudyCharacterAttributeSet, MaxMana, OldValue);
	
	OnManaChanged.Broadcast(nullptr,nullptr,nullptr,GetMaxMana()-OldValue.GetCurrentValue(),OldValue.GetCurrentValue(),GetMaxMana());
}

void UUE_GAS_StudyCharacterAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUE_GAS_StudyCharacterAttributeSet, Stamina, OldValue);
}

void UUE_GAS_StudyCharacterAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUE_GAS_StudyCharacterAttributeSet, MaxStamina, OldValue);
}

void UUE_GAS_StudyCharacterAttributeSet::OnRep_Attack(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUE_GAS_StudyCharacterAttributeSet, Attack, OldValue);
}

void UUE_GAS_StudyCharacterAttributeSet::OnRep_Defense(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUE_GAS_StudyCharacterAttributeSet, Defense, OldValue);
}

void UUE_GAS_StudyCharacterAttributeSet::OnRep_Exp(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUE_GAS_StudyCharacterAttributeSet, Exp, OldValue);
}

void UUE_GAS_StudyCharacterAttributeSet::OnRep_MaxExp(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUE_GAS_StudyCharacterAttributeSet, MaxExp, OldValue);
}
