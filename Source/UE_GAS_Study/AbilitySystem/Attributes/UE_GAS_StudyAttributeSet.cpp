#include "UE_GAS_StudyAttributeSet.h"

#include "UE_GAS_Study/AbilitySystem/UE_GAS_StudyAbilitySystemComponent.h"

UUE_GAS_StudyAttributeSet::UUE_GAS_StudyAttributeSet()
{
}

UWorld* UUE_GAS_StudyAttributeSet::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);
	return Outer->GetWorld();
}

class UUE_GAS_StudyAbilitySystemComponent* UUE_GAS_StudyAttributeSet::GetGASStudyAbilitySystemComponent() const
{
	return Cast<UUE_GAS_StudyAbilitySystemComponent>(GetOwningAbilitySystemComponent());
}
