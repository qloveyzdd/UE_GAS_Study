#include "UE_GAS_StudyAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "UE_GAS_Study/UE_GAS_StudyLogChannel.h"

const FPrimaryAssetType UUE_GAS_StudyAssetManager::PotionItemType = TEXT("Potion");
const FPrimaryAssetType UUE_GAS_StudyAssetManager::EquipmentItemType = TEXT("Equipment");
const FPrimaryAssetType UUE_GAS_StudyAssetManager::TokenItemType = TEXT("Token");

UUE_GAS_StudyAssetManager& UUE_GAS_StudyAssetManager::Get()
{
	check(GEngine);

	if (UUE_GAS_StudyAssetManager* Singleton = Cast<UUE_GAS_StudyAssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	UE_LOG(LogGAS_Study, Fatal,
	       TEXT("Invalid AssetManagerClassName in DefaultEngine.ini, must be UE_GAS_StudyAssetManager!"));
	return *NewObject<UUE_GAS_StudyAssetManager>();
}

const class UUE_GAS_StudyGameData& UUE_GAS_StudyAssetManager::GetGameData()
{
	return GetOrLoadTypedGameData<UUE_GAS_StudyGameData>(GAS_StudyGameDataPath);
}

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

UPrimaryDataAsset* UUE_GAS_StudyAssetManager::LoadGameDataOfClass(TSubclassOf<UPrimaryDataAsset> DataClass,
                                                                  const TSoftObjectPtr<UPrimaryDataAsset>&
                                                                  DataClassPath, FPrimaryAssetType PrimaryAssetType)
{
	UPrimaryDataAsset* Asset = nullptr;

	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("Loading GameData Object"), STAT_GameData, STATGROUP_LoadTime);
	if (!DataClassPath.IsNull())
	{
#if WITH_EDITOR
		FScopedSlowTask SlowTask(0, FText::Format(
			                         NSLOCTEXT("UE_GAS_StudyEditor", "BeginLoadGameDataTask", "Loading GameData {0}"),
			                         FText::FromName(DataClass->GetFName())));
		const bool bShowCancelButton = false;
		const bool bAllowInPIE = true;
		SlowTask.MakeDialog(bShowCancelButton, bAllowInPIE);
#endif

		UE_LOG(LogGAS_Study, Log, TEXT("Loading GameData: %s ..."), *DataClassPath.ToString());
		SCOPE_LOG_TIME_IN_SECONDS(TEXT("... GameData Loaded!"), nullptr);

		if (GIsEditor)
		{
			Asset = DataClassPath.LoadSynchronous();
			LoadPrimaryAssetsWithType(PrimaryAssetType);
		}
		else
		{
			TSharedPtr<FStreamableHandle> Handle = LoadPrimaryAssetsWithType(PrimaryAssetType);
			if (Handle.IsValid())
			{
				Handle->WaitUntilComplete(0.0f, false);

				Asset = Cast<UPrimaryDataAsset>(Handle->GetLoadedAsset());
			}
		}
	}
	if (Asset)
	{
		GameDataMap.Add(DataClass, Asset);
	}
	else
	{
		UE_LOG(LogGAS_Study, Fatal,
		       TEXT(
			       "Failed to Load GameData Asset at %s. Type %s. This is not recoverable and likely means you do not have the correct data to run %s."
		       ), *DataClassPath.ToString(), *DataClass->GetName(), *GetName());
	}

	return Asset;
}

UObject* UUE_GAS_StudyAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
	if (AssetPath.IsValid())
	{
		TUniquePtr<FScopeLogTime> LogTimePtr;

		if (ShouldLogAssetLoads())
		{
			UE_LOG(LogGAS_Study, Log, TEXT("Synchronously loading asset: %s"), *AssetPath.ToString());
			LogTimePtr = MakeUnique<FScopeLogTime>(TEXT("... Asset Loaded!"), nullptr);
		}
		if (UAssetManager::IsInitialized())
		{
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath, false);
		}

		return AssetPath.TryLoad();
	}
	return nullptr;
}

bool UUE_GAS_StudyAssetManager::ShouldLogAssetLoads()
{
	static bool bLogAssetLoads = FParse::Param(FCommandLine::Get(), TEXT("LogAssetLoads"));
	return bLogAssetLoads;
}

void UUE_GAS_StudyAssetManager::AddLoadedAsset(const UObject* Asset)
{
	if (ensure(Asset))
	{
		FScopeLock LoadedAssetsLock(&LoadedAssetsCritical);
		LoadedAssets.Add(Asset);
	}
}
