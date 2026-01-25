// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE_GAS_Study/UI/Core/UI_SlotBase.h"
#include "UI_EquipmentSlot.generated.h"

/**
 * 
 */
UCLASS()
class UE_GAS_STUDY_API UUI_EquipmentSlot : public UUI_SlotBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<class UUI_ICONDragDrog> ICONDragDrogClass;
	
public:
	UUI_EquipmentSlot(const FObjectInitializer& ObjectInitializer);
	
public:
	UPROPERTY()
	int32 EquipmentId;
	
public:
	virtual void OnClickedWidget() override;
	
public:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
									  UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
							  UDragDropOperation* InOperation) override;
};
