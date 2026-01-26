// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UE_GAS_StudyGameData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType,Const ,meta=(DisplayName="UE_GAS_StudyGameData",ShortTooltip="UE_GAS_StudyGameData"))
class UE_GAS_STUDY_API UUE_GAS_StudyGameData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UUE_GAS_StudyGameData();
	
	static const UUE_GAS_StudyGameData& Get();
	
public:
	UPROPERTY(EditDefaultsOnly,Category="Default Gameplay Effects",meta = (DisplayName="Default Gameplay Effects"))
	TSoftClassPtr<class UGameplayEffect> DamageGameplayEffect_SetByCaller;
	
	UPROPERTY(EditDefaultsOnly,Category="Default Gameplay Effects",meta = (DisplayName="Default Gameplay Effects"))
	TSoftClassPtr<class UGameplayEffect> HealthGameplayEffect_SetByCaller;
	
	UPROPERTY(EditDefaultsOnly,Category="Default Gameplay Effects")
	TSoftClassPtr<class UGameplayEffect> DynamicTagGameplayEffect;
};
