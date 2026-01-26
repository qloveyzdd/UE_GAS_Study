// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayCueInterface.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/Character.h"
#include "UE_GAS_StudyCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGenericAbilityCoolDownDelegate, FGameplayTagContainer, OutAbilityTag, float, CoolDownTime);

UCLASS(config=Game)
class UE_GAS_STUDY_API AUE_GAS_StudyCharacterBase : public ACharacter, public IAbilitySystemInterface,
                                                    public IGameplayCueInterface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

protected:
	//引入GAS组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UE_GAS_Study|GAS", meta=(AllowPrivateAccess=true))
	TObjectPtr<class UUE_GAS_StudyAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<const class UUE_GAS_StudyCharacterAttributeSet> CharacterSet;

	//连击组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UE_GAS_Study|Character", meta=(AllowPrivateAccess=true))
	TObjectPtr<class UUE_GAS_StudyComboComponent> ComboComponent;
	//生命组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UE_GAS_Study|Character", meta=(AllowPrivateAccess=true))
	TObjectPtr<class UUE_GAS_StudyHealthComponent> HealthComponent;
	//背包组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UE_GAS_Study|Character", meta=(AllowPrivateAccess=true))
	TObjectPtr<class UUE_GAS_StudyInventoryComponent> InventoryComponent;
	//装备组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UE_GAS_Study|Character", meta=(AllowPrivateAccess=true))
	TObjectPtr<class UUE_GAS_StudyEquipmentComponent> EquipmentComponent;

public:
	AUE_GAS_StudyCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	virtual void OnDeathStarted(AActor* OwningActor);
	UFUNCTION()
	virtual void OnDeathFinished(AActor* OwningActor);
	
	void DisableMovementAndCollision();
	
	void DestroyDueToDeath();
	void UninitAndDestroy();
	
	UFUNCTION(BlueprintImplementableEvent,meta=(DisplayName="OnDeathFinished"))
	void K2_OnDeathFinished();

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="UE_GAS_Study|Ability", meta=(AllowPrivateAccess=true))
	TMap<FGameplayTag, TSubclassOf<class UUE_GAS_StudyGameplayAbility>> AbilitiesToAdd;

	TMap<FGameplayTag, FGameplayAbilitySpecHandle> AbilitiesToActive;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="UE_GAS_Study|Ability", meta=(AllowPrivateAccess=true))
	TSubclassOf<UUE_GAS_StudyGameplayAbility> DeathAbilityClass;
	
	FGameplayAbilitySpecHandle DeathAbilityHandle;

public:
	UFUNCTION(BlueprintCallable, Category="UE_GAS_Study|Character")
	class UUE_GAS_StudyAbilitySystemComponent* GetGASStudyAbilitySystemComponent() const;
	UFUNCTION(BlueprintCallable, Category="UE_GAS_Study|Character")
	class UUE_GAS_StudyComboComponent* GetGASStudyComboComponent() const;
	UFUNCTION(BlueprintCallable, Category="UE_GAS_Study|Character")
	class UUE_GAS_StudyHealthComponent* GetGASStudyHealthComponent() const;

	UFUNCTION(BlueprintCallable, Category="UE_GAS_Study|Character")
	class AUE_GAS_StudyPlayerController* GetGASStudyPlayerController() const;

	UFUNCTION(BlueprintCallable, Category="UE_GAS_Study|Character")
	class AUE_GAS_StudyPlayerState* GetGASStudyPlayerState() const;
	
	UFUNCTION(BlueprintCallable, Category="UE_GAS_Study|Character")
	class UUE_GAS_StudyInventoryComponent* GetGASStudyInventoryComponent() const;
	UFUNCTION(BlueprintCallable, Category="UE_GAS_Study|Character")
	class UUE_GAS_StudyEquipmentComponent* GetGASStudyEquipmentComponent() const;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//获取自身标签
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	//匹配标签
	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;
	//匹配所有标签
	virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	//具有对应标签
	virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	
public:
	
	UPROPERTY(BlueprintAssignable)
	FGenericAbilityCoolDownDelegate AbilityCoolDownDelegate;
	
protected:
	UFUNCTION(BlueprintCallable, Client,Reliable)
	void ClientRPCFunction(FGameplayTagContainer OutAbilityTag, float CoolDownTime);
public:
	UFUNCTION(Server,Reliable)
	void ActiveSkillByInventoryId(int32 InInventoryId);
	
public:
	UFUNCTION(Server,Reliable)
	void CallServerDownLoadInfo();
	
	UFUNCTION(Server,Reliable)
	void SwapInventoryItem(int32 Index_i,int32 Index_j);
	
	UFUNCTION(Server,Reliable)
	void UndockEquipmentById(int32 InUndockEquipmentID);
	
	UFUNCTION(Server,Reliable)
	void SwapEquipmentItem(int32 Index_i,int32 Index_j);
	
	UFUNCTION(Server,Reliable)
	void SwapFromInventoryToEquipment(int32 InInventory_Index,int32 InEquipment_Index);
	
	UFUNCTION(Server,Reliable)
	void SwapFromEquipmentToInventory(int32 InEquipment_Index,int32 InInventory_Index);
};
