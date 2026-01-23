#include "UE_GAS_StudyAssetManager.h"

#include "AbilitySystemGlobals.h"

const FPrimaryAssetType UUE_GAS_StudyAssetManager::PotionItemType = TEXT("Potion");
const FPrimaryAssetType UUE_GAS_StudyAssetManager::EquipmentItemType= TEXT("Equipment");
const FPrimaryAssetType UUE_GAS_StudyAssetManager::TokenItemType= TEXT("Token");

UUE_GAS_StudyAssetManager::UUE_GAS_StudyAssetManager()
{
}

void UUE_GAS_StudyAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	//TODO
	UAbilitySystemGlobals::Get().InitGlobalData();
}

UUE_GAS_StudyAssetManager* UUE_GAS_StudyAssetManager::ForceLoadItem(
	const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning)
{
	return nullptr;
}
