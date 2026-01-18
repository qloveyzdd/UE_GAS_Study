// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "UE_GAS_StudyHitBox.generated.h"

UCLASS(BlueprintType, Blueprintable)
class UE_GAS_STUDY_API AUE_GAS_StudyHitBox : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HitCollision", meta=(AllowPrivateAccess="true"))
	class USceneComponent* HitCollisionRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HitCollision", meta=(AllowPrivateAccess="true"))
	class UBoxComponent* HitDamage;

public:
	AUE_GAS_StudyHitBox(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION()
	virtual void HandleDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                          const FHitResult& SweepResult);

	virtual UPrimitiveComponent* GetHitDamage();

	void SetHitDamageRelativePosition(const FVector& InNewPostion);

	void SetBoxExtent(const FVector& InNewBoxExtent);

	void SetBuffs(const TArray<struct FGameplayTagContainer>& InBuffs);

	bool IsExist(class AUE_GAS_StudyCharacterBase* InNewTaget) const;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY()
	TArray<FGameplayTagContainer> BuffsTags;
	
	UPROPERTY()
	TArray<TWeakObjectPtr<AUE_GAS_StudyCharacterBase>> AttackedTarget;
};
