// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "UE_GAS_StudyAssetManager.generated.h"

UCLASS(Config = Game)
class UE_GAS_STUDY_API UUE_GAS_StudyAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	UUE_GAS_StudyAssetManager();

	virtual void StartInitialLoading() override;

	static const FPrimaryAssetType PotionItemType;
	static const FPrimaryAssetType EquipmentItemType;
	static const FPrimaryAssetType TokenItemType;

	static UUE_GAS_StudyAssetManager& Get();
	
	template <typename AssetType>
	static TSubclassOf<AssetType> GetSubclass(const TSoftClassPtr<AssetType>& AssetPointer,bool bKeepInMemory = true);

	const class UUE_GAS_StudyGameData& GetGameData();

	UUE_GAS_StudyAssetManager* ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning = true);

protected:
	template <typename GameDataClass>
	const GameDataClass& GetOrLoadTypedGameData(const TSoftObjectPtr<GameDataClass>& DataPath)
	{
		if (TObjectPtr<UPrimaryDataAsset> const* pResult = GameDataMap.Find(GameDataClass::StaticClass()))
		{
			return *CastChecked<GameDataClass>(*pResult);
		}
		return *CastChecked<const GameDataClass>(
			LoadGameDataOfClass(GameDataClass::StaticClass(), DataPath, GameDataClass::StaticClass()->GetFName()));
	}

	UPrimaryDataAsset* LoadGameDataOfClass(TSubclassOf<UPrimaryDataAsset> DataClass,
	                                       const TSoftObjectPtr<UPrimaryDataAsset>& DataClassPath,
	                                       FPrimaryAssetType PrimaryAssetType);

	static UObject* SynchronousLoadAsset(const FSoftObjectPath& AssetPath);

	static bool ShouldLogAssetLoads();

	void AddLoadedAsset(const UObject* Asset);

protected:
	UPROPERTY(Config)
	TSoftObjectPtr<class UUE_GAS_StudyGameData> GAS_StudyGameDataPath;

	UPROPERTY(Transient)
	TMap<TObjectPtr<UClass>, TObjectPtr<UPrimaryDataAsset>> GameDataMap;

private:
	UPROPERTY()
	TSet<TObjectPtr<const UObject>> LoadedAssets;

	FCriticalSection LoadedAssetsCritical;
};

template <typename AssetType>
TSubclassOf<AssetType> UUE_GAS_StudyAssetManager::GetSubclass(const TSoftClassPtr<AssetType>& AssetPointer,bool bKeepInMemory)
{
	TSubclassOf<AssetType> LoadedSubclass;
	
	const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();
	
	if (AssetPath.IsValid())
	{
		LoadedSubclass = AssetPointer.Get();
		if (!LoadedSubclass)
		{
			LoadedSubclass = Cast<UClass>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedSubclass,TEXT("Failed to Load Asset Class [%s]"),*AssetPath.ToString());
		}
		if (LoadedSubclass&&bKeepInMemory)
		{
			Get().AddLoadedAsset(Cast<UObject>(LoadedSubclass));
		}
	}
	return LoadedSubclass;
}