#include "UE_GAS_StudyDamageExecution_Air.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "UE_GAS_Study/AbilitySystem/Attributes/UE_GAS_StudyCharacterAttributeSet.h"

struct FDamageAirStatics
{
	FGameplayEffectAttributeCaptureDefinition BaseDamageAirDef;

	FDamageAirStatics()
	{
		BaseDamageAirDef = FGameplayEffectAttributeCaptureDefinition(
			UUE_GAS_StudyCharacterAttributeSet::GetDamageAttribute(), EGameplayEffectAttributeCaptureSource::Source,
			true);
	}
};

static FDamageAirStatics& DamageAirStatics()
{
	static FDamageAirStatics Statics;
	return Statics;
}

UUE_GAS_StudyDamageExecution_Air::UUE_GAS_StudyDamageExecution_Air()
{
	RelevantAttributesToCapture.Add(DamageAirStatics().BaseDamageAirDef);
}

void UUE_GAS_StudyDamageExecution_Air::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

#if WITH_SERVER_CODE

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayEffectContextHandle& EffectContextHandle = Spec.GetEffectContext();

	AActor* EffectCauser = EffectContextHandle.GetEffectCauser();

	UAbilitySystemComponent* EffectASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(EffectCauser);

	UAbilitySystemComponent* OriginalASC = EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	float Defence = 0.0f;
	if (const UUE_GAS_StudyCharacterAttributeSet* EffectArr = Cast<UUE_GAS_StudyCharacterAttributeSet>(
		EffectASC->GetAttributeSet(UUE_GAS_StudyCharacterAttributeSet::StaticClass())))
	{
		Defence = EffectArr->GetDefense();
	}

	float Attack = 0.0f;
	if (const UUE_GAS_StudyCharacterAttributeSet* OriginalArr = Cast<UUE_GAS_StudyCharacterAttributeSet>(
		OriginalASC->GetAttributeSet(UUE_GAS_StudyCharacterAttributeSet::StaticClass())))
	{
		Attack = OriginalArr->GetAttack();
	}

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float BaseAirDamage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageAirStatics().BaseDamageAirDef,
	                                                           EvaluateParameters, BaseAirDamage);

	const float BaseAirDamageDone = FMath::Max(0.0f, BaseAirDamage + Attack - Defence);

	if (BaseAirDamageDone > 0.0f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
			UUE_GAS_StudyCharacterAttributeSet::GetDamageAttribute(), EGameplayModOp::Additive, BaseAirDamageDone));
	}


#endif
}
