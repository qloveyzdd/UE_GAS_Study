// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE_GAS_Study/UI/Core/UI_Base.h"
#include "UI_InventoryPanel.generated.h"

/**
 * 
 */
UCLASS()
class UE_GAS_STUDY_API UUI_InventoryPanel : public UUI_Base
{
	GENERATED_BODY()

private:
	UPROPERTY(meta=(BindWidget))
	class UUniformGridPanel* InventoryArray;

	UPROPERTY(EditDefaultsOnly, Category=UI)
	TSubclassOf<class UUI_InventorySlot> SlotClass;
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UFUNCTION()
	void OnInventoryItemChanged(const TArray<struct FUE_GAS_StudyInventoryItem>& InInventoryItems);
};
