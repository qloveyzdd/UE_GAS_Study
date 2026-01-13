// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_StopSpeed.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UAnimNotifyState_StopSpeed::UAnimNotifyState_StopSpeed()
	: MaxWalkingSpeed(0.0f)
{
}

void UAnimNotifyState_StopSpeed::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                             float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		MaxWalkingSpeed = InCharacter->GetCharacterMovement()->MaxWalkSpeed;
		MinAnalogWalkingSpeed = InCharacter->GetCharacterMovement()->MinAnalogWalkSpeed;
		InCharacter->GetCharacterMovement()->MaxWalkSpeed = 0.0f;
		InCharacter->GetCharacterMovement()->MinAnalogWalkSpeed = 0.0f;
	}
}

void UAnimNotifyState_StopSpeed::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                            float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UAnimNotifyState_StopSpeed::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                           const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		InCharacter->GetCharacterMovement()->MaxWalkSpeed = MaxWalkingSpeed;
		InCharacter->GetCharacterMovement()->MinAnalogWalkSpeed = MinAnalogWalkingSpeed;
	}
}
