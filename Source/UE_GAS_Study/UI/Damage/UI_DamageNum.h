// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE_GAS_Study/UI/Core/UI_Base.h"
#include "UI_DamageNum.generated.h"

/**
 * 
 */
UCLASS()
class UE_GAS_STUDY_API UUI_DamageNum : public UUI_Base
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NumText;
public:
	virtual void NativeConstruct() override;
	
	void UpdateNum(const FText& InText);
	void UpdateNumColor(const FLinearColor& InColor);
};
