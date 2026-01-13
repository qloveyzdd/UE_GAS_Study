// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_NextCombo.h"

#include "UE_GAS_Study/Character/UE_GAS_StudyCharacter.h"
#include "UE_GAS_Study/Character/UE_GAS_StudyCharacterBase.h"
#include "UE_GAS_Study/Component/UE_GAS_StudyComboComponent.h"

UAnimNotifyState_NextCombo::UAnimNotifyState_NextCombo()
{
}

void UAnimNotifyState_NextCombo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                             float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (MeshComp->GetOuter() && MeshComp->GetOuter()->GetWorld() &&
		!MeshComp->GetOuter()->GetWorld()->IsNetMode(NM_DedicatedServer))
	{
		if (AUE_GAS_StudyCharacterBase* InCharacter = Cast<AUE_GAS_StudyCharacterBase>(MeshComp->GetOuter()))
		{
			InCharacter->GetGASStudyComboComponent()->ResetPressed();
		}
	}
}

void UAnimNotifyState_NextCombo::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                            float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UAnimNotifyState_NextCombo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                           const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	
	if (MeshComp->GetOuter() && MeshComp->GetOuter()->GetWorld() &&
		!MeshComp->GetOuter()->GetWorld()->IsNetMode(NM_DedicatedServer))
	{
		if (AUE_GAS_StudyCharacter* InCharacter = Cast<AUE_GAS_StudyCharacter>(MeshComp->GetOuter()))
		{
			if (InCharacter->GetGASStudyComboComponent()->IsStillPressed())
			{
				InCharacter->ComboMelee();
			}
		}
	}
}
