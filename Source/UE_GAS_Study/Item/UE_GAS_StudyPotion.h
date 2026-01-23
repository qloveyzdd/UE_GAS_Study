// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE_GAS_StudyItemBase.h"
#include "UE_GAS_StudyPotion.generated.h"

/**
 * 
 */
UCLASS()
class UE_GAS_STUDY_API UUE_GAS_StudyPotion : public UUE_GAS_StudyItemBase
{
	GENERATED_BODY()

public:
	UUE_GAS_StudyPotion();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="abilities")
	TSubclassOf<class UUE_GAS_StudyGameplayAbility> GrantedAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="abilities")
	int32 AbilityLevel;
};
