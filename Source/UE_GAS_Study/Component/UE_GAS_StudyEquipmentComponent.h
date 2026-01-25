// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "UE_GAS_StudyComponentBase.h"
#include "UE_GAS_StudyEquipmentComponent.generated.h"

USTRUCT(BlueprintType)
struct FUE_GAS_StudyEquipmentItem
{
	GENERATED_BODY()

public:
	FUE_GAS_StudyEquipmentItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UE_GAS_StudyEquipmentItem")
	class UUE_GAS_StudyEquipment* RPGEquipmentItemPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UE_GAS_StudyEquipmentItem")
	FActiveGameplayEffectHandle ActiveEquipmentEffectHandle;

	bool IsValid() const;

	void ResetSelf();
};

DECLARE_DELEGATE_OneParam(FOnEquipmentItemChangedNative, const TArray<FUE_GAS_StudyEquipmentItem>&);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UE_GAS_STUDY_API UUE_GAS_StudyEquipmentComponent : public UUE_GAS_StudyComponentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUE_GAS_StudyEquipmentComponent(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
public:
	UFUNCTION(Client, Reliable)
	void EquipmentItemChange(const TArray<FUE_GAS_StudyEquipmentItem>& ClientEquipmentItems);
	
	void CallServerDownLoadInfo();
	
public:
	UFUNCTION(BlueprintCallable, Category="Equipment")
	bool AddEquipmentItem(const FUE_GAS_StudyEquipmentItem& NewItem);
	
	UFUNCTION(BlueprintCallable, Category="Equipment")
	void UndockEquipmentById(int32 InUndockEquipmentID);
	
	UFUNCTION(BlueprintCallable, Category="Equipment")
	bool RemoveEquipmentItem(int32 Index_Remove);
	
public:
	UFUNCTION(BlueprintCallable, Category="Equipment")
	void SwapEuipmentItem(int32 Index_i, int32 Index_j);
	UFUNCTION(BlueprintCallable, Category="Equipment")
	void SwapFromInventoryToEquipment(int32 InventoryIndex, int32 EquipmentIndex);
	UFUNCTION(BlueprintCallable, Category="Equipment")
	void SwapFromEquipmentToInventory(int32 EquipmentIndex, int32 InventoryIndex);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing= OnRep_EquipmentItems, Category="Equipment")
	TArray<FUE_GAS_StudyEquipmentItem> EquipmentItems;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	FOnEquipmentItemChangedNative OnEquipmentItemChanged;

	UFUNCTION()
	void OnRep_EquipmentItems();
};
