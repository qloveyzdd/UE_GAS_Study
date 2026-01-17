// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CharacterInfo.h"

#include "Components/TextBlock.h"
#include "UE_GAS_Study/AbilitySystem/UE_GAS_StudyAbilitySystemComponent.h"
#include "UE_GAS_Study/AbilitySystem/Attributes/UE_GAS_StudyCharacterAttributeSet.h"
#include "UE_GAS_Study/Character/UE_GAS_StudyCharacterBase.h"

void UUI_CharacterInfo::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUI_CharacterInfo::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUI_CharacterInfo::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (AUE_GAS_StudyCharacterBase* InCharacter = GetGASStudyCharacterBase())
	{
		if (UUE_GAS_StudyAbilitySystemComponent* InASC = InCharacter->GetGASStudyAbilitySystemComponent())
		{
			if (const UUE_GAS_StudyCharacterAttributeSet* InAttribute = Cast<UUE_GAS_StudyCharacterAttributeSet>(
				InASC->GetAttributeSet(UUE_GAS_StudyCharacterAttributeSet::StaticClass())))
			{
				if (Health)
				{
					float HealthNum = InAttribute->GetHealth();
					float MaxHealthNum = InAttribute->GetMaxHealth();

					FString HealthString = FString::Printf(TEXT("%s"), *FString::SanitizeFloat(HealthNum));
					FString MaxHealthString = FString::Printf(TEXT("%s"), *FString::SanitizeFloat(MaxHealthNum));

					Health->SetText(FText::FromString(HealthString + "/" + MaxHealthString));
				}
				if (Mana)
				{
					float ManaNum = InAttribute->GetMana();
					float MaxManaNum = InAttribute->GetMaxMana();

					FString ManaString = FString::Printf(TEXT("%s"), *FString::SanitizeFloat(ManaNum));
					FString MaxManaString = FString::Printf(TEXT("%s"), *FString::SanitizeFloat(MaxManaNum));

					Mana->SetText(FText::FromString(ManaString + "/" + MaxManaString));
				}
				if (Stamina)
				{
					float StaminaNum = InAttribute->GetStamina();

					FString StaminaString = FString::Printf(TEXT("%s"), *FString::SanitizeFloat(StaminaNum));
					
					Stamina->SetText(FText::FromString(StaminaString));
				}
				if (Attack)
				{
					float AttackNum = InAttribute->GetAttack();

					FString AttackString = FString::Printf(TEXT("%s"), *FString::SanitizeFloat(AttackNum));
					
					Attack->SetText(FText::FromString(AttackString));
				}
				if (Defense)
				{
					float DefenseNum = InAttribute->GetDefense();

					FString DefenseString = FString::Printf(TEXT("%s"), *FString::SanitizeFloat(DefenseNum));
					
					Defense->SetText(FText::FromString(DefenseString));
				}
				if (Exp)
				{
					float ExpNum = InAttribute->GetExp();
					float MaxExpNum = InAttribute->GetMaxExp();

					FString ExpString = FString::Printf(TEXT("%s"), *FString::SanitizeFloat(ExpNum));
					FString MaxExpString = FString::Printf(TEXT("%s"), *FString::SanitizeFloat(MaxExpNum));
					
					Exp->SetText(FText::FromString(ExpString + "/" + MaxExpString));
				}
				
			}
		}
	}
}
