// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_EquipmentSlot.h"

#include "Blueprint/DragDropOperation.h"
#include "Components/Image.h"
#include "UE_GAS_Study/Character/UE_GAS_StudyCharacterBase.h"
#include "UE_GAS_Study/Component/UE_GAS_StudyInventoryComponent.h"
#include "UE_GAS_Study/Item/UE_GAS_StudyEquipment.h"
#include "UE_GAS_Study/Item/UE_GAS_StudyItemBase.h"
#include "UE_GAS_Study/UI/Common/UI_ICONDragDrog.h"
#include "UE_GAS_Study/UI/Inventory/UI_InventorySlot.h"

UUI_EquipmentSlot::UUI_EquipmentSlot(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SlotType = ESlotType::SlotType_EquipmentSlot;
}

void UUI_EquipmentSlot::OnClickedWidget()
{
	Super::OnClickedWidget();

	if (AUE_GAS_StudyCharacterBase* InCharacter = GetGASStudyCharacterBase())
	{
		InCharacter->UndockEquipmentById(EquipmentId);
	}
}

FReply UUI_EquipmentSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton || InMouseEvent.IsTouchEvent())
	{
		FReply Reply = FReply::Handled();

		TSharedPtr<SWidget> SlateWidgetDrag = GetCachedWidget();

		if (SlateWidgetDrag.IsValid())
		{
			Reply.DetectDrag(SlateWidgetDrag.ToSharedRef(), EKeys::RightMouseButton);
			return Reply;
		}
	}

	return FReply::Handled();
}

void UUI_EquipmentSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                             UDragDropOperation*& OutOperation)
{
	if (ICONDragDrogClass && SlotIcon && SlotIcon->GetBrush().GetResourceObject())
	{
		if (UUI_ICONDragDrog* ICONDragDrog = CreateWidget<UUI_ICONDragDrog>(GetWorld(), ICONDragDrogClass))
		{
			if (UDragDropOperation* InDropOperation = NewObject<UDragDropOperation>(
				GetTransientPackage(), UDragDropOperation::StaticClass()))
			{
				// InDropOperation->SetFlags(RF_StrongRefOnFrame);
				ICONDragDrog->DrawICON(Cast<UTexture2D>(SlotIcon->GetBrush().GetResourceObject()));

				InDropOperation->DefaultDragVisual = ICONDragDrog;

				InDropOperation->Payload = this;
				OutOperation = InDropOperation;
				HideSlotIcon();
			}
		}
	}
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

bool UUI_EquipmentSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                     UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	bool bDrop = false;

	if (InOperation)
	{
		if (AUE_GAS_StudyCharacterBase* InCharacter = GetGASStudyCharacterBase())
		{
			if (UUI_SlotBase* InSlotBase = Cast<UUI_SlotBase>(InOperation->Payload))
			{
				ESlotType InSlotType = InSlotBase->GetSlotType();

				switch (InSlotType)
				{
				case ESlotType::SlotType_None:
					check(false);
					bDrop = true;
					break;
				case ESlotType::SlotType_InventorySlot:
					if (UUI_InventorySlot* MyInventorySlot = Cast<UUI_InventorySlot>(InOperation->Payload))
					{
						if (UUE_GAS_StudyItemBase* InRPGItem = InCharacter->GetGASStudyInventoryComponent()->
						                                                    GetInventoryItemByID(
							                                                    MyInventorySlot->InventoryId))
						{
							if (Cast<UUE_GAS_StudyEquipment>(InRPGItem))
							{
								InCharacter->SwapFromInventoryToEquipment(MyInventorySlot->InventoryId, EquipmentId);
								bDrop = true;
							}
							else
							{
								MyInventorySlot->ShowSlotIcon();
								MyInventorySlot->ShowInventoryNum();
								bDrop = true;
							}
						}
					}
					break;
				case ESlotType::SlotType_EquipmentSlot:
					if (UUI_EquipmentSlot* MyEquipmentSlot = Cast<UUI_EquipmentSlot>(InOperation->Payload))
					{
						InCharacter->SwapEquipmentItem(MyEquipmentSlot->EquipmentId, EquipmentId);
						bDrop = true;
					}
					break;
				case ESlotType::SlotType_SkillPanelSlot:
					check(false);
					bDrop = true;
					break;
				default:
					break;
				}
			}
		}
	}

	return bDrop;
}
