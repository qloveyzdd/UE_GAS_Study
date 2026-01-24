// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_ICONDragDrog.h"

#include "Components/Image.h"


// Sets default values for this component's properties
UUI_ICONDragDrog::UUI_ICONDragDrog(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UUI_ICONDragDrog::DrawICON(UTexture2D* InICON)
{
	ICON->SetBrushFromTexture(InICON);
}

