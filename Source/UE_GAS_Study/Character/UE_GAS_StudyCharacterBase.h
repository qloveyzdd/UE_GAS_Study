// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayCueInterface.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/Character.h"
#include "UE_GAS_StudyCharacterBase.generated.h"

UCLASS(config=Game)
class UE_GAS_STUDY_API AUE_GAS_StudyCharacterBase : public ACharacter, public IAbilitySystemInterface,
                                                    public IGameplayCueInterface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

protected:
	//引入GAS组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UE_GAS_Study|GAS", meta=(AllowPrivateAccess=true))
	TObjectPtr<class UUE_GAS_StudyAbilitySystemComponent> AbilitySystemComponent;
	//联机组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UE_GAS_Study|Character", meta=(AllowPrivateAccess=true))
	TObjectPtr<class UUE_GAS_StudyComboComponent> ComboComponent;

public:
	AUE_GAS_StudyCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="UE_GAS_Study|Ability", meta=(AllowPrivateAccess=true))
	TMap<FGameplayTag,TSubclassOf<class UUE_GAS_StudyGameplayAbility>> AbilitiesToAdd;
	
	TMap<FGameplayTag,FGameplayAbilitySpecHandle> AbilitiesToActive;

public:
	UFUNCTION(BlueprintCallable, Category="UE_GAS_Study|Character")
	class UUE_GAS_StudyAbilitySystemComponent* GetGASStudyAbilitySystemComponent() const;
	UFUNCTION(BlueprintCallable, Category="UE_GAS_Study|Character")
	class UUE_GAS_StudyComboComponent* GetGASStudyComboComponent() const;

	UFUNCTION(BlueprintCallable, Category="UE_GAS_Study|Character")
	class AUE_GAS_StudyPlayerController* GetGASStudyPlayerController() const;

	UFUNCTION(BlueprintCallable, Category="UE_GAS_Study|Character")
	class AUE_GAS_StudyPlayerState* GetGASStudyPlayerState() const;

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
};
