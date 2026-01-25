// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_EquipmentSlot.h"

#include "UE_GAS_Study/Character/UE_GAS_StudyCharacterBase.h"
#include "UE_GAS_Study/Component/UE_GAS_StudyEquipmentComponent.h"

UUI_EquipmentSlot::UUI_EquipmentSlot(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
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
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UUI_EquipmentSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

bool UUI_EquipmentSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
