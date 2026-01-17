// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Base.h"

#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "UE_GAS_Study/Character/UE_GAS_StudyCharacterBase.h"

UUI_Base::UUI_Base(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UUI_Base::PlayWidgetAnim(const FString& InAnimName)
{
	if (UWidgetAnimation* TempAnimation = GetNameWidgetAnimation(InAnimName))
	{
		PlayAnimation(TempAnimation);
	}
}

UWidgetAnimation* UUI_Base::GetNameWidgetAnimation(const FString& InWidgetName) const
{
	if (UWidgetBlueprintGeneratedClass* WidgetBlueprintGenerated =
		Cast<UWidgetBlueprintGeneratedClass>(GetClass()))
	{
		TArray<UWidgetAnimation*> TArrayAnimations = WidgetBlueprintGenerated->Animations;

		UWidgetAnimation** MyTempAnimation = TArrayAnimations.FindByPredicate(
			[&](const UWidgetAnimation* OurAnimation)
			{
				return OurAnimation->GetFName().ToString() == InWidgetName + FString("_INST");
			});
		return *MyTempAnimation;
	}

	return nullptr;
}

class AUE_GAS_StudyCharacterBase* UUI_Base::GetGASStudyCharacterBase() const
{
	if (GetWorld())
	{
		if (APlayerController* InPlayerController = GetWorld()->GetFirstPlayerController<APlayerController>())
		{
			if (AUE_GAS_StudyCharacterBase* InCharacter = InPlayerController->GetPawn<AUE_GAS_StudyCharacterBase>())
			{
				return InCharacter;
			}
		}
	}
	return nullptr;
}
