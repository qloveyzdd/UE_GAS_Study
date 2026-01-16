// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "AttributeSet.h"

#include "UE_GAS_StudyAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


struct FGameplayEffectSpec;
DECLARE_MULTICAST_DELEGATE_SixParams(FUE_GAS_StudyAttributeEvent,
	AActor* /*EffectInstigator*/,
	AActor* /*EffectCauser*/,
	const FGameplayEffectSpec* /*EffectSpec*/,
	float /*EffectMagnitude*/,
	float /*OldValue*/,
	float /*NewValue*/);


UCLASS()
class UE_GAS_STUDY_API UUE_GAS_StudyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UUE_GAS_StudyAttributeSet();

	virtual UWorld* GetWorld() const override;

	class UUE_GAS_StudyAbilitySystemComponent* GetGASStudyAbilitySystemComponent() const;
};
