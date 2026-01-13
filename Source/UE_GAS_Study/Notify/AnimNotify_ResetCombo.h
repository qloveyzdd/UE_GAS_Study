// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AnimNotify_ResetCombo.generated.h"

/**
 * 
 */
UCLASS()
class UE_GAS_STUDY_API UAnimNotify_ResetCombo : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_ResetCombo();
	
	virtual FString GetNotifyName_Implementation() const override;
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
