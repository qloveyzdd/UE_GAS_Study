// Fill out your copyright notice in the Description page of Project Settings.


#include "UE_GAS_StudyEquipmentComponent.h"

#include "UE_GAS_StudyInventoryComponent.h"
#include "Net/UnrealNetwork.h"
#include "UE_GAS_Study/AbilitySystem/UE_GAS_StudyAbilitySystemComponent.h"
#include "UE_GAS_Study/Character/UE_GAS_StudyCharacterBase.h"
#include "UE_GAS_Study/Item/UE_GAS_StudyEquipment.h"


FUE_GAS_StudyEquipmentItem::FUE_GAS_StudyEquipmentItem()
	: RPGEquipmentItemPoint(nullptr)
{
}

bool FUE_GAS_StudyEquipmentItem::IsValid() const
{
	if (RPGEquipmentItemPoint)
	{
		return true;
	}
	return false;
}

void FUE_GAS_StudyEquipmentItem::ResetSelf()
{
	ActiveEquipmentEffectHandle.Invalidate();

	RPGEquipmentItemPoint = nullptr;
}

// Sets default values for this component's properties
UUE_GAS_StudyEquipmentComponent::UUE_GAS_StudyEquipmentComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UUE_GAS_StudyEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UUE_GAS_StudyEquipmentComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                                    FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UUE_GAS_StudyEquipmentComponent::AddEquipmentItem(const FUE_GAS_StudyEquipmentItem& NewItem)
{
	UUE_GAS_StudyAbilitySystemComponent* ASC = Cast<AUE_GAS_StudyCharacterBase>(GetOwner())->
		GetGASStudyAbilitySystemComponent();

	if (HasAuthority())
	{
		if (!NewItem.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("AddInventoryItem: Invalid Equipment Item"));
			return false;
		}
		for (int i = 0; i < EquipmentItems.Num(); ++i)
		{
			if (!EquipmentItems[i].IsValid())
			{
				EquipmentItems[i] = NewItem;

				const FGameplayEffectSpecHandle NewHandle = ASC->MakeOutgoingSpec(
					EquipmentItems[i].RPGEquipmentItemPoint->GameplayEffectClass, 1.0f, ASC->MakeEffectContext());
				EquipmentItems[i].ActiveEquipmentEffectHandle = ASC->ApplyGameplayEffectSpecToSelf(*NewHandle.Data);

				// EquipmentItemChange(EquipmentItems);
				return true;
			}
		}
	}

	return false;
}

void UUE_GAS_StudyEquipmentComponent::UndockEquipmentById(int32 InUndockEquipmentID)
{
	if (HasAuthority())
	{
		UUE_GAS_StudyInventoryComponent* InventoryComponent = Cast<UUE_GAS_StudyInventoryComponent>(
			GetOwner()->FindComponentByClass(UUE_GAS_StudyInventoryComponent::StaticClass()));

		if (EquipmentItems[InUndockEquipmentID].IsValid())
		{
			FUE_GAS_StudyEquipmentItem* UndockEquipment = &EquipmentItems[InUndockEquipmentID];

			FUE_GAS_StudyInventoryItem AddInventoryItem;
			AddInventoryItem.GAS_StudyItem = UndockEquipment->RPGEquipmentItemPoint;
			AddInventoryItem.ItemCount = 1;

			if (InventoryComponent->AddInventoryItem(AddInventoryItem))
			{
				RemoveEquipmentItem(InUndockEquipmentID);
			}
		}
	}
}

bool UUE_GAS_StudyEquipmentComponent::RemoveEquipmentItem(int32 Index_Remove)
{
	UUE_GAS_StudyAbilitySystemComponent* ASC = Cast<AUE_GAS_StudyCharacterBase>(GetOwner())->
		GetGASStudyAbilitySystemComponent();
	if (FUE_GAS_StudyEquipmentItem* UndockEquipment = &EquipmentItems[Index_Remove])
	{
		if (UndockEquipment->IsValid())
		{
			ASC->RemoveActiveGameplayEffect(UndockEquipment->ActiveEquipmentEffectHandle);

			UndockEquipment->ResetSelf();

			// EquipmentItemChange(EquipmentItems);
			return true;
		}
	}
	return false;
}

void UUE_GAS_StudyEquipmentComponent::SwapFromInventoryToEquipment(int32 InventoryIndex, int32 EquipmentIndex)
{
}

void UUE_GAS_StudyEquipmentComponent::SwapFromEquipmentToInventory(int32 EquipmentIndex, int32 InventoryIndex)
{
}

void UUE_GAS_StudyEquipmentComponent::SwapEuipmentItem(int32 Index_i, int32 Index_j)
{
	if (Index_i != Index_j
		&& Index_i > INDEX_NONE && Index_i < EquipmentItems.Num()
		&& Index_j > INDEX_NONE && Index_j < EquipmentItems.Num())
	{
		EquipmentItems.Swap(Index_i, Index_j);

		EquipmentItemChange(EquipmentItems);
	}
}

void UUE_GAS_StudyEquipmentComponent::EquipmentItemChange_Implementation(
	const TArray<FUE_GAS_StudyEquipmentItem>& ClientEquipmentItems)
{
	OnEquipmentItemChanged.ExecuteIfBound(EquipmentItems);
}

void UUE_GAS_StudyEquipmentComponent::GetLifetimeReplicatedProps(
	TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UUE_GAS_StudyEquipmentComponent, EquipmentItems);
}

void UUE_GAS_StudyEquipmentComponent::OnRep_EquipmentItems()
{
	OnEquipmentItemChanged.ExecuteIfBound(EquipmentItems);

	EquipmentItems.AddDefaulted(6);
}
