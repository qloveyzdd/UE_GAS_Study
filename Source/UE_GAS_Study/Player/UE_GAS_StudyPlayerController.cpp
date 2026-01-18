#include "UE_GAS_StudyPlayerController.h"

#include "UE_GAS_StudyPlayerState.h"
#include "UE_GAS_Study/AbilitySystem/UE_GAS_StudyAbilitySystemComponent.h"
#include "UE_GAS_Study/Character/UE_GAS_StudyCharacterBase.h"
#include "UE_GAS_Study/FeedBack/NumberPopComponent/UE_GAS_StudyNumberPopComponent.h"
#include "UE_GAS_Study/FeedBack/NumberPopComponent/UE_GAS_StudyNumberPopComponent_UMG.h"
#include "UE_GAS_Study/UI/UE_GAS_StudyHUD.h"

AUE_GAS_StudyPlayerController::AUE_GAS_StudyPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NumberPopComponent = CreateDefaultSubobject<UUE_GAS_StudyNumberPopComponent_UMG>(TEXT("NumberPopComponent"));
	NumberPopComponent->SetIsReplicated(false);
}

void AUE_GAS_StudyPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if (UUE_GAS_StudyAbilitySystemComponent* ASC = GetGASStudyAbilitySystemComponent())
	{
		ASC->ProcessAbilityInput(DeltaTime,bGamePaused);
	}
	Super::PostProcessInput(DeltaTime, bGamePaused);
}

class UUE_GAS_StudyNumberPopComponent* AUE_GAS_StudyPlayerController::GetGASStudyNumberPopComponent() const
{
	return CastChecked<UUE_GAS_StudyNumberPopComponent>(NumberPopComponent, ECastCheckedType::NullAllowed);
}

class AUE_GAS_StudyPlayerState* AUE_GAS_StudyPlayerController::GetGASStudyPlayerState() const
{
	//可以选择，是否允许为空，如果允许则找不到时返回空值
	return CastChecked<AUE_GAS_StudyPlayerState>(PlayerState, ECastCheckedType::NullAllowed);
}

class AUE_GAS_StudyHUD* AUE_GAS_StudyPlayerController::GetGASStudyHUD() const
{
	//可以选择，是否允许为空，如果允许则找不到时返回空值
	return CastChecked<AUE_GAS_StudyHUD>(GetHUD(), ECastCheckedType::NullAllowed);
}

class UUE_GAS_StudyAbilitySystemComponent* AUE_GAS_StudyPlayerController::GetGASStudyAbilitySystemComponent() const
{
	AUE_GAS_StudyCharacterBase* Gas_StudyCharacterBase = Cast<AUE_GAS_StudyCharacterBase>(GetPawn());
	if (Gas_StudyCharacterBase)
	{
		return Gas_StudyCharacterBase->GetGASStudyAbilitySystemComponent();
	}
	return nullptr;
}
