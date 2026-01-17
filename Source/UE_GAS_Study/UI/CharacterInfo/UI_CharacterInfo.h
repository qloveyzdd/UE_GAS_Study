// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE_GAS_Study/UI/Core/UI_Base.h"
#include "UI_CharacterInfo.generated.h"

/**
 * 
 */
UCLASS()
class UE_GAS_STUDY_API UUI_CharacterInfo : public UUI_Base
{
	GENERATED_BODY()

private:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Health;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Mana;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Stamina;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Attack;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Defense;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Exp;
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
