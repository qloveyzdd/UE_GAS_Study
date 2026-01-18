// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "UE_GAS_StudyNumberPopActor.generated.h"

UCLASS()
class UE_GAS_STUDY_API AUE_GAS_StudyNumberPopActor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HitCollision", meta=(AllowPrivateAccess="true"))
	class USceneComponent* DamageNumRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HitCollision", meta=(AllowPrivateAccess="true"))
	class UWidgetComponent* DamageWidgetComponent;

public:
	AUE_GAS_StudyNumberPopActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void UpdateNum(const FText& InText) const;
	void UpdateNumColor(const FLinearColor& InColor) const;
};
