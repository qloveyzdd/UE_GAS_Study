// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UE_GAS_StudyNumberPopComponent.h"
#include "UE_GAS_StudyNumberPopComponent_UMG.generated.h"

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class UE_GAS_STUDY_API UUE_GAS_StudyNumberPopComponent_UMG : public UUE_GAS_StudyNumberPopComponent
{
	GENERATED_BODY()

public:
	UUE_GAS_StudyNumberPopComponent_UMG(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void AddNumberPop(const FUE_GAS_StudyNumberPopRequest& NewRequest) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "GAS_Study|DamageNum",
		meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AUE_GAS_StudyNumberPopActor> NumPopActorClass;
};
