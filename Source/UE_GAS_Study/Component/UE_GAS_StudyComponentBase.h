// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "UE_GAS_StudyComponentBase.generated.h"


UCLASS(ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UE_GAS_STUDY_API UUE_GAS_StudyComponentBase : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UUE_GAS_StudyComponentBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
