// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE_GAS_StudyComponentBase.h"
#include "UE_GAS_StudyEquipmentComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UE_GAS_STUDY_API UUE_GAS_StudyEquipmentComponent : public UUE_GAS_StudyComponentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUE_GAS_StudyEquipmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
