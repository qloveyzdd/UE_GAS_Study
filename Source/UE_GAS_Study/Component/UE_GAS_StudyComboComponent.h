// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE_GAS_StudyComponentBase.h"
#include "UE_GAS_StudyComboComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UE_GAS_STUDY_API UUE_GAS_StudyComboComponent : public UUE_GAS_StudyComponentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUE_GAS_StudyComboComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="GAS_Study|Components")
	TArray<UAnimMontage*> ComboMontages;

	UPROPERTY()
	UAnimMontage* LastPlayMontage = nullptr;

	int32 ComboIndex = 0;
	int32 ComboMaxIndex = 0;

	bool bShortPress = false;

public:
	UFUNCTION(BlueprintCallable, Category="GAS_Study|Components")
	void SetPressed();
	UFUNCTION(BlueprintCallable, Category="GAS_Study|Components")
	void ResetPressed();
	UFUNCTION(BlueprintCallable, Category="GAS_Study|Components")
	bool IsStillPressed();

	UFUNCTION(BlueprintCallable, Category="GAS_Study|Components")
	int32 GetComboIndex();

	UFUNCTION(BlueprintCallable, Category="GAS_Study|Components")
	UAnimMontage* GetComboAnimMontage();
	UFUNCTION(BlueprintCallable, Category="GAS_Study|Components")
	UAnimMontage* GetLastPlayAnimMontage();

	UFUNCTION(BlueprintCallable, Category="GAS_Study|Components")
	void UpdateComboIndex();
	UFUNCTION(BlueprintCallable, Category="GAS_Study|Components")
	void ResetComboIndex();
};
