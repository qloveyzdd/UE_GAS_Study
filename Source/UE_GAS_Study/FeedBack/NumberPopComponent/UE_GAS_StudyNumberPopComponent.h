// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UE_GAS_StudyNumberPopComponent.generated.h"

USTRUCT(BlueprintType)
struct FUE_GAS_StudyNumberPopRequest
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GAS_Study|NumberPop")
	FVector WorldLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GAS_Study|NumberPop")
	FGameplayTagContainer SourceTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GAS_Study|NumberPop")
	FGameplayTagContainer TargetTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GAS_Study|NumberPop")
	int32 NumberToDisplay = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GAS_Study|NumberPop")
	bool bIsCriticalDamage = false;

public:
	FUE_GAS_StudyNumberPopRequest()
		: WorldLocation(ForceInitToZero)
	{
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GAS_Study|NumberPop")
	FColor ColorToDisplay = FColor::Red;
};

UCLASS(Abstract)
class UE_GAS_STUDY_API UUE_GAS_StudyNumberPopComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UUE_GAS_StudyNumberPopComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category= Foo)
	virtual void AddNumberPop(const FUE_GAS_StudyNumberPopRequest& NewRequest)
	{
	}
};
