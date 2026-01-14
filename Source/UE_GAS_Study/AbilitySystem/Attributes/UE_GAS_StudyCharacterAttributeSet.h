// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "AbilitySystemComponent.h"
#include "UE_GAS_StudyAttributeSet.h"
#include "UE_GAS_StudyCharacterAttributeSet.generated.h"

UCLASS()
class UE_GAS_STUDY_API UUE_GAS_StudyCharacterAttributeSet : public UUE_GAS_StudyAttributeSet
{
	GENERATED_BODY()

public:
	UUE_GAS_StudyCharacterAttributeSet();

	void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	ATTRIBUTE_ACCESSORS(UUE_GAS_StudyCharacterAttributeSet, Damage);
	ATTRIBUTE_ACCESSORS(UUE_GAS_StudyCharacterAttributeSet, Level);
	ATTRIBUTE_ACCESSORS(UUE_GAS_StudyCharacterAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UUE_GAS_StudyCharacterAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UUE_GAS_StudyCharacterAttributeSet, Mana);
	ATTRIBUTE_ACCESSORS(UUE_GAS_StudyCharacterAttributeSet, MaxMana);
	ATTRIBUTE_ACCESSORS(UUE_GAS_StudyCharacterAttributeSet, Stamina);
	ATTRIBUTE_ACCESSORS(UUE_GAS_StudyCharacterAttributeSet, MaxStamina);
	ATTRIBUTE_ACCESSORS(UUE_GAS_StudyCharacterAttributeSet, Attack);
	ATTRIBUTE_ACCESSORS(UUE_GAS_StudyCharacterAttributeSet, Defense);
	ATTRIBUTE_ACCESSORS(UUE_GAS_StudyCharacterAttributeSet, Exp);
	ATTRIBUTE_ACCESSORS(UUE_GAS_StudyCharacterAttributeSet, MaxExp);

public:
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

public:
	UFUNCTION()
	virtual void OnRep_Damage(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Level(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Attack(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Defense(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Exp(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_MaxExp(const FGameplayAttributeData& OldValue);

public:
	FUE_GAS_StudyAttributeSet OnHealthChanged;
	FUE_GAS_StudyAttributeSet OnMaxHealthChanged;
	FUE_GAS_StudyAttributeSet OnOutOfHealth;
	FUE_GAS_StudyAttributeSet OnManaChanged;
	FUE_GAS_StudyAttributeSet OnMaxManaChanged;

private:
	UPROPERTY(BlueprintReadOnly, Category="UE_GAS_Study|Attribute", ReplicatedUsing=OnRep_Damage,
		meta=(HideFromModifiers, AllowPrivateAccess=true))
	FGameplayAttributeData Damage;

	UPROPERTY(BlueprintReadOnly, Category="Attribute", ReplicatedUsing=OnRep_Level,
		meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Level;

	UPROPERTY(BlueprintReadOnly, Category="Attribute", ReplicatedUsing=OnRep_Health,
		meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Health;
	UPROPERTY(BlueprintReadOnly, Category="Attribute", ReplicatedUsing=OnRep_MaxHealth,
		meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MaxHealth;

	bool bOutOfHealth;
	float MaxHealthBeforeAttributeChange;
	float HealthBeforeAttributeChange;

	UPROPERTY(BlueprintReadOnly, Category="Attribute", ReplicatedUsing=OnRep_Mana,
		meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Mana;
	UPROPERTY(BlueprintReadOnly, Category="Attribute", ReplicatedUsing=OnRep_MaxMana,
		meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MaxMana;

	UPROPERTY(BlueprintReadOnly, Category="Attribute", ReplicatedUsing=OnRep_Stamina,
		meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Stamina;
	UPROPERTY(BlueprintReadOnly, Category="Attribute", ReplicatedUsing=OnRep_MaxStamina,
		meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MaxStamina;

	UPROPERTY(BlueprintReadOnly, Category="Attribute", ReplicatedUsing=OnRep_Attack,
		meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Attack;

	UPROPERTY(BlueprintReadOnly, Category="Attribute", ReplicatedUsing=OnRep_Defense,
		meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Defense;

	UPROPERTY(BlueprintReadOnly, Category="Attribute", ReplicatedUsing=OnRep_Exp,
		meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Exp;
	UPROPERTY(BlueprintReadOnly, Category="Attribute", ReplicatedUsing=OnRep_MaxExp,
		meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MaxExp;
};
