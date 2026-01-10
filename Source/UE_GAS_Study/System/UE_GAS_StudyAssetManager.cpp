#include "UE_GAS_StudyAssetManager.h"

#include "AbilitySystemGlobals.h"

UUE_GAS_StudyAssetManager::UUE_GAS_StudyAssetManager()
{
}

void UUE_GAS_StudyAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	//TODO
	UAbilitySystemGlobals::Get().InitGlobalData();
}
