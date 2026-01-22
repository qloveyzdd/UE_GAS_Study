#include "UE_GAS_StudyCharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UE_GAS_Study/AbilitySystem/UE_GAS_StudyAbilitySystemComponent.h"
#include "UE_GAS_Study/AbilitySystem/Abilities/UE_GAS_StudyGameplayAbility.h"
#include "UE_GAS_Study/AbilitySystem/Attributes/UE_GAS_StudyCharacterAttributeSet.h"
#include "UE_GAS_Study/Component/UE_GAS_StudyComboComponent.h"
#include "UE_GAS_Study/Component/UE_GAS_StudyHealthComponent.h"
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

	CharacterSet = CreateDefaultSubobject<UUE_GAS_StudyCharacterAttributeSet>(TEXT("CharacterSet"));

	ComboComponent = CreateDefaultSubobject<UUE_GAS_StudyComboComponent>(TEXT("ComboComponent"));
	ComboComponent->SetIsReplicated(false);

	HealthComponent = CreateDefaultSubobject<UUE_GAS_StudyHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDeathStarted.AddDynamic(this, &ThisClass::OnDeathStarted);
	HealthComponent->OnDeathFinished.AddDynamic(this, &ThisClass::OnDeathFinished);
	HealthComponent->SetIsReplicated(true);

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
		
		UUE_GAS_StudyGameplayAbility* DeathAbilityCDO = DeathAbilityClass->GetDefaultObject<UUE_GAS_StudyGameplayAbility>();
		FGameplayAbilitySpec DeathAbilityCDOSpec(DeathAbilityCDO, 1);
		DeathAbilityCDOSpec.SourceObject = this;
		DeathAbilityHandle = AbilitySystemComponent->GiveAbility(DeathAbilityCDOSpec);
		
		AbilitySystemComponent->AbilityCommittedCallbacks.AddLambda(
		[this](UGameplayAbility* InGameplayAbility)
		{
			float CoolDownTime = InGameplayAbility->GetCooldownTimeRemaining();
			FGameplayTagContainer AbilityTags = InGameplayAbility->AbilityTags;
			
			ClientRPCFunction(AbilityTags,CoolDownTime);
		}
		);
		
	}
	HealthComponent->InitializeWithAbilitySystem(AbilitySystemComponent);
}

void AUE_GAS_StudyCharacterBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (AbilitySystemComponent && GetLocalRole() == ENetRole::ROLE_Authority)
	{
		AbilitySystemComponent->ClearAllAbilities();
	}
	Super::EndPlay(EndPlayReason);
}

void AUE_GAS_StudyCharacterBase::OnDeathStarted(AActor* OwningActor)
{
	DisableMovementAndCollision();
}

void AUE_GAS_StudyCharacterBase::OnDeathFinished(AActor* OwningActor)
{
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::DestroyDueToDeath);
}

void AUE_GAS_StudyCharacterBase::DisableMovementAndCollision()
{
	if (Controller)
	{
		Controller->SetIgnoreMoveInput(true);
	}

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	UCharacterMovementComponent* MoveComp = CastChecked<UCharacterMovementComponent>(GetCharacterMovement());
	MoveComp->StopMovementImmediately();
	MoveComp->DisableMovement();
}

void AUE_GAS_StudyCharacterBase::DestroyDueToDeath()
{
	K2_OnDeathFinished();
	UninitAndDestroy();
}

void AUE_GAS_StudyCharacterBase::UninitAndDestroy()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		DetachFromControllerPendingDestroy();
		SetLifeSpan(0.1f);
	}
	HealthComponent->UnInitializeWithAbilitySystem(AbilitySystemComponent);

	SetActorHiddenInGame(true);
}

class UUE_GAS_StudyComboComponent* AUE_GAS_StudyCharacterBase::GetGASStudyComboComponent() const
{
	return CastChecked<UUE_GAS_StudyComboComponent>(ComboComponent, ECastCheckedType::NullAllowed);
}

class UUE_GAS_StudyHealthComponent* AUE_GAS_StudyCharacterBase::GetGASStudyHealthComponent() const
{
	return CastChecked<UUE_GAS_StudyHealthComponent>(HealthComponent, ECastCheckedType::NullAllowed);
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

void AUE_GAS_StudyCharacterBase::ClientRPCFunction_Implementation(FGameplayTagContainer OutAbilityTag,
	float CoolDownTime)
{
	AbilityCoolDownDelegate.Broadcast(OutAbilityTag, CoolDownTime);
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
