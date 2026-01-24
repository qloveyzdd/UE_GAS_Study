// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE_GAS_Study/UI/Core/UI_SlotBase.h"
#include "UI_InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class UE_GAS_STUDY_API UUI_InventorySlot : public UUI_SlotBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<class UUI_ICONDragDrog> ICONDragDrogClass;

public:
	UUI_InventorySlot(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY()
	int32 InventoryId;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Num;

public:
	void HideInventoryNum();
	void ShowInventoryNum();
	
	virtual  void OnClickedWidget() override;
};
