#include "UE_GAS_StudyGameplayAbility.h"

#include "UE_GAS_Study/AbilitySystem/UE_GAS_StudyAbilitySystemComponent.h"
#include "UE_GAS_Study/Character/UE_GAS_StudyCharacterBase.h"
#include "UE_GAS_Study/Player/UE_GAS_StudyPlayerController.h"

UUE_GAS_StudyGameplayAbility::UUE_GAS_StudyGameplayAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//是否同步
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
	//如何实例化
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	//如何执行
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	//如何触发
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::ClientOrServer;
}

UUE_GAS_StudyAbilitySystemComponent* UUE_GAS_StudyGameplayAbility::GetGas_StudyAbilitySystemComponentFromActorInfo() const
{
	return CurrentActorInfo
		       ? CastChecked<UUE_GAS_StudyAbilitySystemComponent>(
			       CurrentActorInfo->AbilitySystemComponent.Get(), ECastCheckedType::NullAllowed)
		       : nullptr;
}

class AUE_GAS_StudyCharacterBase* UUE_GAS_StudyGameplayAbility::GetGas_StudyCharacterFromActorInfo() const
{
	return CurrentActorInfo
			   ? CastChecked<AUE_GAS_StudyCharacterBase>(
				   CurrentActorInfo->AvatarActor.Get(), ECastCheckedType::NullAllowed)
			   : nullptr;
}

class AController* UUE_GAS_StudyGameplayAbility::GetGas_StudyControllerFromActorInfo() const
{
	if (CurrentActorInfo)
	{
		if (AController* PC = CurrentActorInfo->PlayerController.Get())
		{
			return PC;
		}
		AActor* TestActor = CurrentActorInfo->OwnerActor.Get();
		while (TestActor)
		{
			if (AController* C = Cast<AController>(TestActor))
			{
				return C;
			}
			if (APawn* TestPawn = Cast<APawn>(TestActor))
			{
				return TestPawn->GetController();
			}
			TestActor = TestActor->GetOwner();
		}
	}
	return nullptr;
}

class AUE_GAS_StudyPlayerController* UUE_GAS_StudyGameplayAbility::GetGas_StudyPlayerControllerFromActorInfo() const
{
	return CurrentActorInfo
			   ? CastChecked<AUE_GAS_StudyPlayerController>(
				   CurrentActorInfo->PlayerController.Get(), ECastCheckedType::NullAllowed)
			   : nullptr;
}
