// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_AddForce.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

FVector UAnimNotifyState_AddForce::GetCurrentCharacterDirection(ACharacter* InCharacter)
{
	FVector V = FVector::ZeroVector;

	if (InCharacter)
	{
		if (DirectionForce.X != 0.0f)
		{
			V += InCharacter->GetActorForwardVector() * DirectionForce.X;
		}
		else if (DirectionForce.Y != 0.0f)
		{
			V += InCharacter->GetActorRightVector() * DirectionForce.Y;
		}
		else if (DirectionForce.Z != 0.0f)
		{
			V += InCharacter->GetActorUpVector() * DirectionForce.Z;
		}
	}

	return V;
}

UAnimNotifyState_AddForce::UAnimNotifyState_AddForce()
	: Super(), TotalDurationConsuming(0.0f), ForceSizeConsuming(0.0f),
	  DirectionForce(1.0f, 0.0f, 0.0f), ForceSize(180000.0f)
{
}

void UAnimNotifyState_AddForce::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                            float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		FVector NewFirection = GetCurrentCharacterDirection(InCharacter);
		InCharacter->GetCharacterMovement()->AddImpulse(ForceSize * NewFirection, true);
	}
}

void UAnimNotifyState_AddForce::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                           float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UAnimNotifyState_AddForce::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                          const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		InCharacter->GetCharacterMovement()->StopMovementImmediately();
	}
}
