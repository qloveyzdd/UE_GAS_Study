// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_GameMain.h"

#include "Blueprint/DragDropOperation.h"
#include "Equipment/UI_EquipmentSlot.h"
#include "Inventory/UI_InventorySlot.h"
#include "UE_GAS_Study/Character/UE_GAS_StudyCharacterBase.h"



UUI_GameMain::UUI_GameMain(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UUI_GameMain::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUI_GameMain::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUI_GameMain::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

bool UUI_GameMain::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	bool bDrop = false;
	if (InOperation)
	{
		if (AUE_GAS_StudyCharacterBase* InCharacter = GetGASStudyCharacterBase())
		{
			if (UUI_InventorySlot* MyInventorySlot = Cast<UUI_InventorySlot>(InOperation->Payload))
			{
				MyInventorySlot->ShowSlotIcon();
				MyInventorySlot->ShowInventoryNum();
				bDrop = true;
			}
			else if (UUI_EquipmentSlot* MyEquipmentSlot = Cast<UUI_EquipmentSlot>(InOperation->Payload))
			{
				MyEquipmentSlot->ShowSlotIcon();
				bDrop = true;
			}
		}
	}
	return bDrop;
}
