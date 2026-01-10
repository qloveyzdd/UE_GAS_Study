#include "UE_GAS_StudyComponentBase.h"

UUE_GAS_StudyComponentBase::UUE_GAS_StudyComponentBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
}
