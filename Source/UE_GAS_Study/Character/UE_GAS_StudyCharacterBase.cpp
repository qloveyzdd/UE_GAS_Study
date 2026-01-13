#include "UE_GAS_StudyCharacterBase.h"

#include "UE_GAS_Study/AbilitySystem/UE_GAS_StudyAbilitySystemComponent.h"
#include "UE_GAS_Study/AbilitySystem/Abilities/UE_GAS_StudyGameplayAbility.h"
#include "UE_GAS_Study/Component/UE_GAS_StudyComboComponent.h"
#include "UE_GAS_Study/Player/UE_GAS_StudyPlayerController.h"
#include "UE_GAS_Study/Player/UE_GAS_StudyPlayerState.h"


AUE_GAS_StudyCharacterBase::AUE_GAS_StudyCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	AbilitySystemComponent = CreateDefaultSubobject<
		UUE_GAS_StudyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	//同步内容多少可调节
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);


	ComboComponent = CreateDefaultSubobject<
		UUE_GAS_StudyComboComponent>(TEXT("ComboComponent"));
	ComboComponent->SetIsReplicated(false);


	//同步频率更新
	NetUpdateFrequency = 100.0f;
}

void AUE_GAS_StudyCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	//GAS只能在服务器上注册
	if (AbilitySystemComponent && GetLocalRole() == ENetRole::ROLE_Authority)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		//批量注册能力
		for (auto& TempAbilityPair : AbilitiesToAdd)
		{
			UUE_GAS_StudyGameplayAbility* AbilityCDO = TempAbilityPair.Value->
			                                                           GetDefaultObject<UUE_GAS_StudyGameplayAbility>();
			FGameplayAbilitySpec AbilitySpec(AbilityCDO, 1);
			AbilitySpec.SourceObject = this;
			AbilitySpec.DynamicAbilityTags.AddTag(TempAbilityPair.Key);
			//向GAS系统组件注册能力
			const FGameplayAbilitySpecHandle AbilitySpecHandle = AbilitySystemComponent->GiveAbility(AbilitySpec);

			AbilitiesToActive.Add(TempAbilityPair.Key, AbilitySpecHandle);
		}
	}
}

void AUE_GAS_StudyCharacterBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

class UUE_GAS_StudyComboComponent* AUE_GAS_StudyCharacterBase::GetGASStudyComboComponent() const
{
	return CastChecked<UUE_GAS_StudyComboComponent>(ComboComponent, ECastCheckedType::NullAllowed);
}

UAbilitySystemComponent* AUE_GAS_StudyCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AUE_GAS_StudyCharacterBase::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	if (const UUE_GAS_StudyAbilitySystemComponent* GAS = GetGASStudyAbilitySystemComponent())
	{
		GAS->GetOwnedGameplayTags(TagContainer);
	}
}

bool AUE_GAS_StudyCharacterBase::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	if (const UUE_GAS_StudyAbilitySystemComponent* GAS = GetGASStudyAbilitySystemComponent())
	{
		return GAS->HasMatchingGameplayTag(TagToCheck);
	}
	return false;
}

bool AUE_GAS_StudyCharacterBase::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	if (const UUE_GAS_StudyAbilitySystemComponent* GAS = GetGASStudyAbilitySystemComponent())
	{
		return GAS->HasAllMatchingGameplayTags(TagContainer);
	}
	return false;
}

bool AUE_GAS_StudyCharacterBase::HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	if (const UUE_GAS_StudyAbilitySystemComponent* GAS = GetGASStudyAbilitySystemComponent())
	{
		return GAS->HasAnyMatchingGameplayTags(TagContainer);
	}
	return false;
}

class AUE_GAS_StudyPlayerState* AUE_GAS_StudyCharacterBase::GetGASStudyPlayerState() const
{
	//可以选择，是否允许为空，如果允许则找不到时返回空值
	return CastChecked<AUE_GAS_StudyPlayerState>(GetPlayerState(), ECastCheckedType::NullAllowed);
}

class AUE_GAS_StudyPlayerController* AUE_GAS_StudyCharacterBase::GetGASStudyPlayerController() const
{
	//可以选择，是否允许为空，如果允许则找不到时返回空值
	return CastChecked<AUE_GAS_StudyPlayerController>(Controller, ECastCheckedType::NullAllowed);
}

class UUE_GAS_StudyAbilitySystemComponent* AUE_GAS_StudyCharacterBase::GetGASStudyAbilitySystemComponent() const
{
	return CastChecked<UUE_GAS_StudyAbilitySystemComponent>(AbilitySystemComponent, ECastCheckedType::NullAllowed);
}
