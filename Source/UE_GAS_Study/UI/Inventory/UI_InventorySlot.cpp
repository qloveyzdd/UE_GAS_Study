// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_InventorySlot.h"

#include "Components/TextBlock.h"
#include "UE_GAS_Study/Character/UE_GAS_StudyCharacterBase.h"

UUI_InventorySlot::UUI_InventorySlot(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SlotType = ESlotType::SlotType_InventorySlot;
}

void UUI_InventorySlot::HideInventoryNum()
{
	Num->SetVisibility(ESlateVisibility::Hidden);
}

void UUI_InventorySlot::ShowInventoryNum()
{
	Num->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UUI_InventorySlot::OnClickedWidget()
{
	Super::OnClickedWidget();

	if (AUE_GAS_StudyCharacterBase*InCharacter = GetGASStudyCharacterBase())
	{
		InCharacter->ActiveSkillByInventoryId_Implementation(InventoryId);
	}
}
