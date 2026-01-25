// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_Base.h"
#include "UI_SlotBase.generated.h"

/**
 * 
 */
UCLASS()
class UE_GAS_STUDY_API UUI_SlotBase : public UUI_Base
{
	GENERATED_BODY()
	
protected:
	ESlotType SlotType;

public:
	UUI_SlotBase(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(meta = (BindWidget))
	class UImage* SlotIcon;

	UPROPERTY(meta = (BindWidget))
	class UButton* ClickButton;

	UPROPERTY(EditDefaultsOnly, Category=UI)
	TSubclassOf<class UUI_InformationDescribe> UI_TipClass;

public:
	virtual void NativeConstruct() override;

	void HideSlotIcon();
	void ShowSlotIcon();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category=Tip)
	UWidget* GetSlotTip();

	UFUNCTION()
	virtual void OnClickedWidget();
	
	UFUNCTION()
	ESlotType GetSlotType();
};
