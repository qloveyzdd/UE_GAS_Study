// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_InventoryPanel.h"

#include "UI_InventorySlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "UE_GAS_Study/Character/UE_GAS_StudyCharacterBase.h"
#include "UE_GAS_Study/Component/UE_GAS_StudyInventoryComponent.h"
#include "UE_GAS_Study/Item/UE_GAS_StudyItemBase.h"

void UUI_InventoryPanel::NativeConstruct()
{
	Super::NativeConstruct();

	if (AUE_GAS_StudyCharacterBase* InCharacter = GetGASStudyCharacterBase())
	{
		InCharacter->GetGASStudyInventoryComponent()->OnInventoryItemChanged.BindUObject(this,&UUI_InventoryPanel::OnInventoryItemChanged);
		
		InCharacter->CallServerDownLoadInfo();
	}
}

void UUI_InventoryPanel::NativeDestruct()
{
	Super::NativeDestruct();
	
	if (AUE_GAS_StudyCharacterBase* InCharacter = GetGASStudyCharacterBase())
	{
		InCharacter->GetGASStudyInventoryComponent()->OnInventoryItemChanged.Unbind();
	}
}

void UUI_InventoryPanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UUI_InventoryPanel::OnInventoryItemChanged(const TArray<struct FUE_GAS_StudyInventoryItem>& InInventoryItems)
{
	if (InventoryArray->GetChildrenCount() == 0)
	{
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				if (UUI_InventorySlot* SlotWidget = CreateWidget<UUI_InventorySlot>(GetWorld(),SlotClass))
				{
					SlotWidget->InventoryId = i * 6 + j;
					if (UUniformGridSlot* GridSlot = InventoryArray->AddChildToUniformGrid(SlotWidget,i,j))
					{
						
					}
				}
			}
		}
	}
	if (InInventoryItems.Num() > 0)
	{
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				if (UUI_InventorySlot* InSlot = Cast<UUI_InventorySlot>(InventoryArray->GetChildAt(i * 6 + j)))
				{
					if (InInventoryItems[i * 6 + j].IsValid())
					{
						InSlot->Num->SetText(FText::FromString(FString::FromInt(InInventoryItems[i*6+j].ItemCount)));
						InSlot->Num->SetVisibility(ESlateVisibility::Visible);
						
						InSlot->SlotIcon->SetBrushFromTexture(InInventoryItems[i*6+j].GAS_StudyItem->ItemIcon);
						InSlot->SlotIcon->SetVisibility(ESlateVisibility::Visible);
					}
					else
					{
						InSlot->Num->SetVisibility(ESlateVisibility::Hidden);
						InSlot->SlotIcon->SetVisibility(ESlateVisibility::Hidden);
						InSlot->SlotIcon->SetBrushResourceObject(nullptr);
					}
				}
			}
		}
	}
}
