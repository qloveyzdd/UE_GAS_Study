// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Attack.h"

#include "UE_GAS_Study/DamagedActor/UE_GAS_StudyHitBox.h"

UAnimNotify_Attack::UAnimNotify_Attack()
{
	HitObjectClass = AUE_GAS_StudyHitBox::StaticClass();
	BoxExtent = FVector(32.0f);
	LifeTime = 4.0f;

	InSocketName = TEXT("OpenFire");
}

FString UAnimNotify_Attack::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_Attack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (AActor* InCharacter = Cast<AActor>(MeshComp->GetOuter()))
	{
		FVector ComponentLocation = MeshComp->GetSocketLocation(InSocketName);
		FRotator ComponentRotation = MeshComp->GetSocketRotation(InSocketName);

		if (!InCharacter->GetWorld()->IsNetMode(NM_Client))
		{
			FTransform Transform((ComponentRotation + RotationOffset).Quaternion(), ComponentLocation);

			//延迟生成
			if (AUE_GAS_StudyHitBox* HitCollision = InCharacter->GetWorld()->SpawnActorDeferred<AUE_GAS_StudyHitBox>(
				HitObjectClass, Transform,NULL, Cast<APawn>(InCharacter),
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn))
			{
				HitCollision->SetBuffs(BuffTags);
				HitCollision->SetBoxExtent(BoxExtent);

				FVector RelativeLocation = HitCollision->GetHitDamage()->GetRelativeLocation();
				HitCollision->SetHitDamageRelativePosition(RelativeLocation + RelativeOffsetLocation);
				
				HitCollision->SetLifeSpan(LifeTime);
				
				HitCollision->FinishSpawning(Transform);

				if (bBind)
				{
					HitCollision->AttachToComponent(MeshComp,FAttachmentTransformRules::SnapToTargetIncludingScale,InSocketName);
				}
			}
		}
	}
}
