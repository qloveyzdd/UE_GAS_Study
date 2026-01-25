// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_InventorySlot.h"

#include "Blueprint/DragDropOperation.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "UE_GAS_Study/Character/UE_GAS_StudyCharacterBase.h"
#include "UE_GAS_Study/Component/UE_GAS_StudyInventoryComponent.h"
#include "UE_GAS_Study/UI/Common/UI_ICONDragDrog.h"

UUI_InventorySlot::UUI_InventorySlot(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
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

	if (AUE_GAS_StudyCharacterBase* InCharacter = GetGASStudyCharacterBase())
	{
		InCharacter->ActiveSkillByInventoryId(InventoryId);
	}
}

FReply UUI_InventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
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

void UUI_InventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
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
				HideInventoryNum();
				HideSlotIcon();
			}
		}
	}
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

bool UUI_InventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
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
					InSlotBase->ShowSlotIcon();
					bDrop = true;
					break;
				case ESlotType::SlotType_InventorySlot:
					if (UUI_InventorySlot* MyInventorySlot = Cast<UUI_InventorySlot>(InOperation->Payload))
					{
						InCharacter->SwapInventoryItem(MyInventorySlot->InventoryId, InventoryId);
						bDrop = true;
					}
					break;
				case ESlotType::SlotType_EquipmentSlot:
					break;
				default:
					break;
				}
			}
		}
	}

	return bDrop;
}
