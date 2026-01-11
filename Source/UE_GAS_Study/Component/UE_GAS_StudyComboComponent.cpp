// Fill out your copyright notice in the Description page of Project Settings.


#include "UE_GAS_StudyComboComponent.h"


// Sets default values for this component's properties
UUE_GAS_StudyComboComponent::UUE_GAS_StudyComboComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UUE_GAS_StudyComboComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	check(ComboMontages.Num()>0);
	ComboMaxIndex = ComboMontages.Num() - 1;
}

void UUE_GAS_StudyComboComponent::SetPressed()
{
	bShortPress = true;
}

void UUE_GAS_StudyComboComponent::ResetPressed()
{
	bShortPress = false;
}

bool UUE_GAS_StudyComboComponent::IsStillPressed()
{
	return bShortPress;
}

int32 UUE_GAS_StudyComboComponent::GetComboIndex()
{
	return ComboIndex;
}

UAnimMontage* UUE_GAS_StudyComboComponent::GetComboAnimMontage()
{
	LastPlayMontage = ComboMontages[ComboIndex];
	return ComboMontages[ComboIndex];
}

UAnimMontage* UUE_GAS_StudyComboComponent::GetLastPlayAnimMontage()
{
	return LastPlayMontage;
}

void UUE_GAS_StudyComboComponent::UpdateComboIndex()
{
	ComboIndex++;
	if (ComboIndex > ComboMaxIndex)
	{
		ComboIndex = 0;
	}
}

void UUE_GAS_StudyComboComponent::ResetComboIndex()
{
	ComboIndex = 0;
}
