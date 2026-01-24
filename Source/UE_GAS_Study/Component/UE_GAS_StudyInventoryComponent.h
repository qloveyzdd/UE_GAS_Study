// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE_GAS_StudyComponentBase.h"
#include "UE_GAS_StudyInventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FUE_GAS_StudyInventoryItem
{
	GENERATED_BODY()

public:
	FUE_GAS_StudyInventoryItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UE_GAS_StudyInventoryItem")
	class UUE_GAS_StudyItemBase* GAS_StudyItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UE_GAS_StudyInventoryItem")
	int32 ItemCount;

	bool IsValid() const;

	void ResetSelf();
};

DECLARE_DELEGATE_OneParam(FOnInventoryItemChangedNative, const TArray<FUE_GAS_StudyInventoryItem>&);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UE_GAS_STUDY_API UUE_GAS_StudyInventoryComponent : public UUE_GAS_StudyComponentBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,ReplicatedUsing= OnRep_InventoryItems, Category="Inventory")
	TArray<FUE_GAS_StudyInventoryItem> InventoryItems;
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// Sets default values for this component's properties
	UUE_GAS_StudyInventoryComponent(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	FOnInventoryItemChangedNative OnInventoryItemChanged;
	
	UFUNCTION()
	void OnRep_InventoryItems();
	
public:
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool AddInventoryItem(FUE_GAS_StudyInventoryItem NewItem);
	
	UFUNCTION(BlueprintPure, Category="Inventory")
	bool HasThisInventoryItem(FUE_GAS_StudyInventoryItem NewItem);
	
	bool ReplaceInventoryItem(FUE_GAS_StudyInventoryItem NewItem,int32 InReplace_ID);
	
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RemoveInventoryItem(int32 Index_Remove);
	
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RemoveInventoryItemByItem(FUE_GAS_StudyInventoryItem NewItem);
	
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void SwapInventoryItem(int32 Index_i,int32 Index_j);
	
	UFUNCTION(BlueprintCallable, Category="Inventory")
	UUE_GAS_StudyItemBase* GetInventoryItemByID(int32 i);
	
	UFUNCTION(BlueprintCallable, Category="Inventory")
	FUE_GAS_StudyInventoryItem GetInventoryItemInfoByID(int32 i);
};
