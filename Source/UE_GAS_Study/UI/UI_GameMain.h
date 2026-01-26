// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/UI_Base.h"
#include "UI_GameMain.generated.h"

/**
 * 
 */
UCLASS()
class UE_GAS_STUDY_API UUI_GameMain : public UUI_Base
{
	GENERATED_BODY()
	
public:
	UUI_GameMain(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
