// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_AddForce.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "AddForce"))
class UE_GAS_STUDY_API UAnimNotifyState_AddForce : public UAnimNotifyState
{
	GENERATED_BODY()

private:
	float TotalDurationConsuming;

	float ForceSizeConsuming;

	FVector GetCurrentCharacterDirection(ACharacter* InCharacter);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimNotifyState_AddForce")
	FVector DirectionForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimNotifyState_AddForce")
	float ForceSize;

public:
	UAnimNotifyState_AddForce();

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
	                         const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
	                        const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	                       const FAnimNotifyEventReference& EventReference) override;
};
