// Fill out your copyright notice in the Description page of Project Settings.


#include "UE_GAS_StudyInventoryComponent.h"

#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"
#include "UE_GAS_Study/AbilitySystem/Abilities/UE_GAS_StudyGameplayAbility.h"
#include "UE_GAS_Study/Character/UE_GAS_StudyCharacterBase.h"
#include "UE_GAS_Study/Item/UE_GAS_StudyEquipment.h"
#include "UE_GAS_Study/Item/UE_GAS_StudyItemBase.h"
#include "UE_GAS_Study/Item/UE_GAS_StudyPotion.h"


FUE_GAS_StudyInventoryItem::FUE_GAS_StudyInventoryItem()
	: GAS_StudyItem(nullptr), ItemCount(0)
{
}

bool FUE_GAS_StudyInventoryItem::IsValid() const
{
	if (GAS_StudyItem && ItemCount > 0)
	{
		return true;
	}
	return false;
}

void FUE_GAS_StudyInventoryItem::ResetSelf()
{
	GAS_StudyItem = nullptr;
	ItemCount = 0;
}

void UUE_GAS_StudyInventoryComponent::GetLifetimeReplicatedProps(
	TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UUE_GAS_StudyInventoryComponent, InventoryItems);
}

// Sets default values for this component's properties
UUE_GAS_StudyInventoryComponent::UUE_GAS_StudyInventoryComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	InventoryItems.AddDefaulted(30); // Default 30 inventory slots

	SetIsReplicatedByDefault(true);
}


// Called when the game starts
void UUE_GAS_StudyInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UUE_GAS_StudyInventoryComponent::OnRep_InventoryItems()
{
	OnInventoryItemChanged.ExecuteIfBound(InventoryItems);
}

void UUE_GAS_StudyInventoryComponent::ActiveSkillByInventoryId(int32 InInventoryId)
{
	if (InventoryItems[InInventoryId].IsValid())
	{
		if (UUE_GAS_StudyPotion* InPotion = Cast<UUE_GAS_StudyPotion>(InventoryItems[InInventoryId].GAS_StudyItem))
		{
			UAbilitySystemComponent*AbilitySystemComponent = Cast<AUE_GAS_StudyCharacterBase>(GetOwner())->GetAbilitySystemComponent();
			UUE_GAS_StudyGameplayAbility* InGA = Cast<UUE_GAS_StudyGameplayAbility>(InPotion->GrantedAbility.GetDefaultObject());
			FGameplayAbilitySpecHandle Handle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(InGA));
			AbilitySystemComponent->TryActivateAbility(Handle);
			
			AbilitySystemComponent->SetRemoveAbilityOnEnd(Handle);
		}
		else if (UUE_GAS_StudyEquipment* InEquipment = Cast<UUE_GAS_StudyEquipment>(InventoryItems[InInventoryId].GAS_StudyItem))
		{
			
		}
	}
}

void UUE_GAS_StudyInventoryComponent::CallServerDownLoadInfo()
{
	InventoryItemChange(InventoryItems);
}

void UUE_GAS_StudyInventoryComponent::InventoryItemChange_Implementation(
	const TArray<FUE_GAS_StudyInventoryItem>& ClientInventoryItems)
{
	OnInventoryItemChanged.ExecuteIfBound(InventoryItems);
}

bool UUE_GAS_StudyInventoryComponent::AddInventoryItem(FUE_GAS_StudyInventoryItem NewItem)
{
	if (HasAuthority())
	{
		if (!NewItem.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("AddInventoryItem Failed: Invalid Item"));
			return false;
		}

		for (int i = 0; i < InventoryItems.Num(); ++i)
		{
			if (InventoryItems[i].GAS_StudyItem == NewItem.GAS_StudyItem)
			{
				if (NewItem.GAS_StudyItem->MaxCount > 1)
				{
					InventoryItems[i].ItemCount += NewItem.ItemCount;
					return true;
				}
			}
		}

		for (int i = 0; i < InventoryItems.Num(); ++i)
		{
			if (!InventoryItems[i].IsValid())
			{
				InventoryItems[i] = NewItem;
				return true;
			}
		}
	}
	return false;
}

bool UUE_GAS_StudyInventoryComponent::HasThisInventoryItem(FUE_GAS_StudyInventoryItem NewItem)
{
	for (int i = 0; i < InventoryItems.Num(); ++i)
	{
		if (InventoryItems[i].GAS_StudyItem == NewItem.GAS_StudyItem &&
			InventoryItems[i].ItemCount == NewItem.ItemCount)
		{
			return true;
		}
	}
	return false;
}

bool UUE_GAS_StudyInventoryComponent::ReplaceInventoryItem(FUE_GAS_StudyInventoryItem NewItem, int32 InReplace_ID)
{
	if (HasAuthority())
	{
		InventoryItems[InReplace_ID] = NewItem;

		return true;
	}
	return false;
}

void UUE_GAS_StudyInventoryComponent::RemoveInventoryItem(int32 Index_Remove)
{
	if (HasAuthority())
	{
		InventoryItems[Index_Remove].ResetSelf();
	}
}

void UUE_GAS_StudyInventoryComponent::RemoveInventoryItemByItem(FUE_GAS_StudyInventoryItem NewItem)
{
	if (HasAuthority())
	{
		for (int i = 0; i < InventoryItems.Num(); ++i)
		{
			if (InventoryItems[i].GAS_StudyItem == NewItem.GAS_StudyItem)
			{
				if (InventoryItems[i].ItemCount <= NewItem.ItemCount)
				{
					InventoryItems[i].ResetSelf();
				}
				else
				{
					InventoryItems[i].ItemCount -= NewItem.ItemCount;
				}
				break;
			}
		}
	}
}

void UUE_GAS_StudyInventoryComponent::SwapInventoryItem(int32 Index_i, int32 Index_j)
{
	if (HasAuthority())
	{
		InventoryItems.Swap(Index_i, Index_j);
	}
}

UUE_GAS_StudyItemBase* UUE_GAS_StudyInventoryComponent::GetInventoryItemByID(int32 i)
{
	if (!InventoryItems[i].IsValid())
	{
		return nullptr;
	}
	return InventoryItems[i].GAS_StudyItem;
}

FUE_GAS_StudyInventoryItem UUE_GAS_StudyInventoryComponent::GetInventoryItemInfoByID(int32 i)
{
	return InventoryItems[i];
}
