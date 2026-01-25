// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_EquipmentPanel.h"

#include "UI_EquipmentSlot.h"
#include "Components/Image.h"
#include "Components/WrapBox.h"
#include "UE_GAS_Study/Character/UE_GAS_StudyCharacterBase.h"
#include "UE_GAS_Study/Component/UE_GAS_StudyEquipmentComponent.h"
#include "UE_GAS_Study/Item/UE_GAS_StudyEquipment.h"

void UUI_EquipmentPanel::NativeConstruct()
{
	Super::NativeConstruct();

	if (EquipmentArray->GetChildrenCount() == 0)
	{
		for (int i = 0; i < 6; ++i)
		{
			if (UUI_EquipmentSlot* SlotWidget = CreateWidget<UUI_EquipmentSlot>(GetWorld(), SlotClass))
			{
				SlotWidget->EquipmentId = i;
				if (UWrapBoxSlot* InWrapSlot = EquipmentArray->AddChildToWrapBox(SlotWidget))
				{
				}
			}
		}
	}

	if (AUE_GAS_StudyCharacterBase* InCharacter = GetGASStudyCharacterBase())
	{
		InCharacter->GetGASStudyEquipmentComponent()->OnEquipmentItemChanged.BindUObject(
			this, &UUI_EquipmentPanel::OnEquipmentItemChanged);
		InCharacter->CallServerDownLoadInfo();
	}
}

void UUI_EquipmentPanel::NativeDestruct()
{
	Super::NativeDestruct();

	if (AUE_GAS_StudyCharacterBase* InCharacter = GetGASStudyCharacterBase())
	{
		InCharacter->GetGASStudyEquipmentComponent()->OnEquipmentItemChanged.Unbind();
	}
}

void UUI_EquipmentPanel::OnEquipmentItemChanged(const TArray<struct FUE_GAS_StudyEquipmentItem>& InEquipmentItems)
{
	if (InEquipmentItems.Num() > 0)
	{
		for (int i = 0; i < 6; ++i)
		{
			if (UUI_EquipmentSlot* InSlot = Cast<UUI_EquipmentSlot>(EquipmentArray->GetChildAt(i)))
			{
				if (InEquipmentItems[i].IsValid())
				{
					InSlot->SlotIcon->SetBrushFromTexture(InEquipmentItems[i].RPGEquipmentItemPoint->ItemIcon);
					InSlot->SlotIcon->SetVisibility(ESlateVisibility::Visible);
				}
				else
				{
					InSlot->SlotIcon->SetVisibility(ESlateVisibility::Hidden);
					InSlot->SlotIcon->SetBrushResourceObject(nullptr);
				}
			}
		}
	}
}
