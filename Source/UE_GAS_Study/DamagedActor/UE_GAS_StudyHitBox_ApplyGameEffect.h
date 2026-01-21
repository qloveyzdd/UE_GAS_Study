// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "UE_GAS_StudyHitBox_ApplyGameEffect.generated.h"

UENUM(BlueprintType)
enum class EGAS_StudyHitCollisionType:uint8
{
	HitCollisionType_Short_Range_Attack UMETA(DisplayName = "近程攻击"),
	HitCollisionType_Direct_Line UMETA(DisplayName = "无障碍直线攻击"),
	HitCollisionType_Line UMETA(DisplayName = "指向攻击，例如手枪子弹"),
	HitCollisionType_Track_Line UMETA(DisplayName = "跟踪攻击"),
	HitCollisionType_Range_Line UMETA(DisplayName = "范围伤害，例如手雷"),
	HitCollisionType_Range UMETA(DisplayName = "范围伤害，例如自爆"),
	HitCollisionType_Chain UMETA(DisplayName = "持续攻击，例如电锯"),
};


UCLASS(BlueprintType, Blueprintable)
class UE_GAS_STUDY_API AUE_GAS_StudyHitBox_ApplyGameEffect : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HitCollision", meta=(AllowPrivateAccess="true"))
	class USceneComponent* HitCollisionRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HitCollision", meta=(AllowPrivateAccess="true"))
	class UBoxComponent* HitDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HitCollision", meta=(AllowPrivateAccess="true"))
	class UProjectileMovementComponent* ProjectileMovement;

public:
	UPROPERTY(EditDefaultsOnly, Category="HitCollision")
	EGAS_StudyHitCollisionType HitCollisionType;

protected:
	UPROPERTY()
	TSubclassOf<class UGameplayEffect> EffectClass;

	UPROPERTY()
	TArray<TWeakObjectPtr<class AUE_GAS_StudyCharacterBase>> AttackedTarget;

public:
	AUE_GAS_StudyHitBox_ApplyGameEffect(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	virtual void PreInitCollision(AActor* InMyInstigator);

	UFUNCTION()
	virtual void HandleDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                          const FHitResult& SweepResult);

	virtual UPrimitiveComponent* GetHitDamage();

	void SetHitDamageRelativePosition(const FVector& InNewPostion);

	void SetBoxExtent(const FVector& InNewBoxExtent);

	void SetGameplayEffect(TSubclassOf<UGameplayEffect>& InGE);

	bool IsExist(class AUE_GAS_StudyCharacterBase* InNewTarget) const;
};
