// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UE_GAS_StudyItemBase.generated.h"

/**
 * 
 */
UCLASS()
class UE_GAS_STUDY_API UUE_GAS_StudyItemBase : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UUE_GAS_StudyItemBase();
	
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Item")
	FPrimaryAssetType ItemType;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	FText ItemName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	FText ItemDescription;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	UTexture2D* ItemIcon;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	int32 Price;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Max")
	int32 MaxCount;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Max")
	int32 MaxLevel;
	
public:
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Max")
	bool IsConsumable() const;
	
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Max")
	FString GetIdentifierString() const;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
