// Fill out your copyright notice in the Description page of Project Settings.


#include "UE_GAS_StudyItemBase.h"

UUE_GAS_StudyItemBase::UUE_GAS_StudyItemBase()
	: Price(0), MaxCount(1), MaxLevel(1)
{
}

bool UUE_GAS_StudyItemBase::IsConsumable() const
{
	if (MaxCount <= 0)
	{
		return false;
	}
	return true;
}

FString UUE_GAS_StudyItemBase::GetIdentifierString() const
{
	return GetPrimaryAssetId().ToString();
}

FPrimaryAssetId UUE_GAS_StudyItemBase::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(ItemType, GetFName());
}
