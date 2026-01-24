// Fill out your copyright notice in the Description page of Project Settings.


#include "UE_GAS_StudyEquipmentComponent.h"


// Sets default values for this component's properties
UUE_GAS_StudyEquipmentComponent::UUE_GAS_StudyEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUE_GAS_StudyEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUE_GAS_StudyEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                    FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

