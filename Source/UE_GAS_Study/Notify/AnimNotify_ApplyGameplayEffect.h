// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ApplyGameplayEffect.generated.h"

/**
 * 
 */
UCLASS()
class UE_GAS_STUDY_API UAnimNotify_ApplyGameplayEffect : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="General Configuration")
	TSubclassOf<class UGameplayEffect> EffectClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="General Configuration")
	TSubclassOf<class AUE_GAS_StudyHitBox_ApplyGameEffect> HitObjectClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="General Configuration")
	FVector RelativeOffsetLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="General Configuration")
	FRotator RotationOffset;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="General Configuration")
	float LifeTime;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="General Configuration")
	FName InSocketName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="General Configuration")
	bool bBind;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hit Box")
	FVector BoxExtent;

public:
	UAnimNotify_ApplyGameplayEffect();

	virtual FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	                    const FAnimNotifyEventReference& EventReference) override;
	
	
};
