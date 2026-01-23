// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE_GAS_StudyItemBase.h"
#include "UE_GAS_StudyEquipment.generated.h"

/**
 * 
 */
UCLASS()
class UE_GAS_STUDY_API UUE_GAS_StudyEquipment : public UUE_GAS_StudyItemBase
{
	GENERATED_BODY()

public:
	UUE_GAS_StudyEquipment();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Abilities")
	TSubclassOf<class UGameplayEffect> GameplayEffectClass;
};
