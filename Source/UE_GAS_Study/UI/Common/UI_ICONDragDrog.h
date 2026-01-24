// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE_GAS_Study/UI/Core/UI_Base.h"
#include "UI_ICONDragDrog.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UE_GAS_STUDY_API UUI_ICONDragDrog : public UUI_Base
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UImage* ICON;

public:
	// Sets default values for this component's properties
	UUI_ICONDragDrog(const FObjectInitializer& ObjectInitializer);

	void DrawICON(UTexture2D* InICON);
};
