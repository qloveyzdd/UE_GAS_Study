// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Base.generated.h"

/**
 * 
 */
UCLASS()
class UE_GAS_STUDY_API UUI_Base : public UUserWidget
{
	GENERATED_BODY()

public:
	UUI_Base(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	void PlayWidgetAnim(const FString& InAnimName);

	UWidgetAnimation* GetNameWidgetAnimation(const FString& InWidgetName) const;

	class AUE_GAS_StudyCharacterBase* GetGASStudyCharacterBase() const;
};
