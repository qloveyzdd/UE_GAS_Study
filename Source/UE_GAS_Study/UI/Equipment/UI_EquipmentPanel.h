// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE_GAS_Study/UI/Core/UI_Base.h"
#include "UI_EquipmentPanel.generated.h"

/**
 * 
 */
UCLASS()
class UE_GAS_STUDY_API UUI_EquipmentPanel : public UUI_Base
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta=(BindWidget))
	class UWrapBox* EquipmentArray;

	UPROPERTY(EditDefaultsOnly, Category=UI)
	TSubclassOf<class UUI_EquipmentSlot> SlotClass;
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	UFUNCTION()
	void OnEquipmentItemChanged(const TArray<struct FUE_GAS_StudyEquipmentItem>& InEquipmentItems);
};
