// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ApplyGameplayEffect.h"

#include "UE_GAS_Study/Character/UE_GAS_StudyCharacterBase.h"
#include "UE_GAS_Study/DamagedActor/UE_GAS_StudyHitBox_ApplyGameEffect.h"

UAnimNotify_ApplyGameplayEffect::UAnimNotify_ApplyGameplayEffect()
{
	HitObjectClass = AUE_GAS_StudyHitBox_ApplyGameEffect::StaticClass();
	BoxExtent = FVector(32.0f);
	LifeTime = 4.0f;

	InSocketName = TEXT("OpenFire");
}

FString UAnimNotify_ApplyGameplayEffect::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_ApplyGameplayEffect::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                             const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (AActor* InCharacter = Cast<AActor>(MeshComp->GetOuter()))
	{
		if (InCharacter->GetWorld()->GetNetMode() != NM_Client)
		{
			FVector ComponentLocation = MeshComp->GetSocketLocation(InSocketName);
			FRotator ComponentRotation = MeshComp->GetSocketRotation(InSocketName);

			AUE_GAS_StudyCharacterBase* CheckCharacter = Cast<AUE_GAS_StudyCharacterBase>(InCharacter);

			//在编辑状态下和运行状态下不同
			if (!CheckCharacter)
			{
				ComponentRotation += FRotator(0.0f, 90.0f, 0.0f);
			}

			FTransform Transform((ComponentRotation + RotationOffset).Quaternion(), ComponentLocation);
			FString VForward = ComponentLocation.ToString();

			//延迟生成
			if (AUE_GAS_StudyHitBox_ApplyGameEffect* HitCollision = InCharacter->GetWorld()->SpawnActorDeferred<
				AUE_GAS_StudyHitBox_ApplyGameEffect>(HitObjectClass, Transform,NULL, Cast<APawn>(InCharacter),
				                                     ESpawnActorCollisionHandlingMethod::AlwaysSpawn))
			{
				HitCollision->PreInitCollision(InCharacter);
				HitCollision->SetGameplayEffect(EffectClass);

				HitCollision->SetBoxExtent(BoxExtent);

				FVector RelativeLocation = HitCollision->GetHitDamage()->GetRelativeLocation();
				HitCollision->SetHitDamageRelativePosition(RelativeLocation + RelativeOffsetLocation);

				HitCollision->SetLifeSpan(LifeTime);

				HitCollision->FinishSpawning(Transform);

				if (bBind)
				{
					HitCollision->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetIncludingScale,
					                                InSocketName);
				}
			}
		}
	}
}
