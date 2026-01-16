// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "UE_GAS_StudyComponentBase.h"
#include "UE_GAS_StudyHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGAS_StudyHealth_DeathEvent, AActor*, OwningActor);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FGAS_StudyHealth_AttributeChange,
                                              UUE_GAS_StudyHealthComponent*, HealthComponent,
                                              float, OldValue, float, NewValue, AActor*, Instigator);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_Damage);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_DamageImmunity);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_DamageSelfDestruct);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_FellOutOfWorld);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_Message);


UENUM(BlueprintType)
enum class EGAS_StudyDeathState:uint8
{
	NotDead = 0,
	DeathStarted,
	DeathFinished
};

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class UE_GAS_STUDY_API UUE_GAS_StudyHealthComponent : public UUE_GAS_StudyComponentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUE_GAS_StudyHealthComponent(const FObjectInitializer& ObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(ReplicatedUsing=OnRep_DeathState)
	EGAS_StudyDeathState DeathState;
	UFUNCTION()
	virtual void OnRep_DeathState(EGAS_StudyDeathState OldState);

	UPROPERTY()
	TObjectPtr<class UUE_GAS_StudyAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<const class UUE_GAS_StudyCharacterAttributeSet> HealthSet;

public:
	UFUNCTION(BlueprintPure, Category="GAS_Study|Health")
	static UUE_GAS_StudyHealthComponent* FindHealthComponent(const AActor* Actor);

	UFUNCTION(BlueprintCallable, Category="GAS_Study|Health")
	void InitializeWithAbilitySystem(class UUE_GAS_StudyAbilitySystemComponent* InASC);

	UFUNCTION(BlueprintCallable, Category="GAS_Study|Health")
	void UnInitializeWithAbilitySystem(class UUE_GAS_StudyAbilitySystemComponent* InASC);

public:
	UFUNCTION(BlueprintCallable, Category="GAS_Study|Health")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category="GAS_Study|Health")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category="GAS_Study|Health")
	float GetMana() const;
	UFUNCTION(BlueprintCallable, Category="GAS_Study|Health")
	float GetMaxMana() const;

	UFUNCTION(BlueprintCallable, Category="GAS_Study|Health")
	float GetHealthNormalized() const;
	UFUNCTION(BlueprintCallable, Category="GAS_Study|Health")
	float GetManaNormalized() const;

	UFUNCTION(BlueprintCallable, Category="GAS_Study|Health")
	EGAS_StudyDeathState GetDeathState() const;

	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category="GAS_Study|Health",
		meta=(ExpandBoolAsExecs = "ReturnValue"))
	bool IsDeadOrDying() const;

	virtual void StartDeath();
	virtual void FinishDeath();
	//跌落死亡
	virtual void DamageSelfDestroy(bool bFellOutOfWorld = false);

public:
	UPROPERTY(BlueprintAssignable)
	FGAS_StudyHealth_AttributeChange OnHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FGAS_StudyHealth_AttributeChange OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FGAS_StudyHealth_AttributeChange OnManaChanged;
	UPROPERTY(BlueprintAssignable)
	FGAS_StudyHealth_AttributeChange OnMaxManaChanged;
	
	
	UPROPERTY(BlueprintAssignable)
	FGAS_StudyHealth_DeathEvent OnDeathStarted;
	UPROPERTY(BlueprintAssignable)
	FGAS_StudyHealth_DeathEvent OnDeathFinished;

protected:
	virtual void OnUnregister() override;

	void ClearGameplayTags();


	virtual void HandleHealthChanged(AActor* DamageInstigator, AActor* DamageCauser,
	                                 const struct FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude,
	                                 float OldValue, float NewValue);
	virtual void HandleMaxHealthChanged(AActor* DamageInstigator, AActor* DamageCauser,
	                                    const struct FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude,
	                                    float OldValue, float NewValue);
	virtual void HandleOutOfChanged(AActor* DamageInstigator, AActor* DamageCauser,
	                                const struct FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude,
	                                float OldValue, float NewValue);
	virtual void HandleManaChanged(AActor* DamageInstigator, AActor* DamageCauser,
	                               const struct FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude,
	                               float OldValue, float NewValue);
	virtual void HandleMaxManaChanged(AActor* DamageInstigator, AActor* DamageCauser,
	                                  const struct FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude,
	                                  float OldValue, float NewValue);
};
