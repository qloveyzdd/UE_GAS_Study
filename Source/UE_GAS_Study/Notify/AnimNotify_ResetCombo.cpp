// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ResetCombo.h"

#include "UE_GAS_Study/Character/UE_GAS_StudyCharacterBase.h"
#include "UE_GAS_Study/Component/UE_GAS_StudyComboComponent.h"

UAnimNotify_ResetCombo::UAnimNotify_ResetCombo()
{
}

FString UAnimNotify_ResetCombo::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_ResetCombo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (AUE_GAS_StudyCharacterBase* UE_GAS_StudyCharacterBase = Cast<AUE_GAS_StudyCharacterBase>(MeshComp->GetOwner()))
	{
		UE_GAS_StudyCharacterBase->GetGASStudyComboComponent()->ResetComboIndex();
	}
}
