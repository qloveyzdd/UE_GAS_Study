// Fill out your copyright notice in the Description page of Project Settings.


#include "UE_GAS_StudyGameData.h"

#include "UE_GAS_StudyAssetManager.h"

UUE_GAS_StudyGameData::UUE_GAS_StudyGameData()
{
}

const UUE_GAS_StudyGameData& UUE_GAS_StudyGameData::Get()
{
	return UUE_GAS_StudyAssetManager::Get().GetGameData();
}
