#include "UE_GAS_StudyNumberPopActor.h"

#include "Components/WidgetComponent.h"
#include "UE_GAS_Study/UI/Damage/UI_DamageNum.h"

AUE_GAS_StudyNumberPopActor::AUE_GAS_StudyNumberPopActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	DamageNumRootComponent = CreateDefaultSubobject<USceneComponent>("DamageNumRootComponent");
	RootComponent = DamageNumRootComponent;

	DamageWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("DamageWidget");
	DamageWidgetComponent->SetupAttachment(RootComponent);
	DamageWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	InitialLifeSpan = 4.0f;
}

void AUE_GAS_StudyNumberPopActor::UpdateNum(const FText& InText) const
{
	if (DamageWidgetComponent)
	{
		if (UUI_DamageNum* Damage = Cast<UUI_DamageNum>(DamageWidgetComponent->GetUserWidgetObject()))
		{
			Damage->UpdateNum(InText);
		}
	}
}

void AUE_GAS_StudyNumberPopActor::UpdateNumColor(const FLinearColor& InColor) const
{
	if (DamageWidgetComponent)
	{
		if (UUI_DamageNum* Damage = Cast<UUI_DamageNum>(DamageWidgetComponent->GetUserWidgetObject()))
		{
			Damage->UpdateNumColor(InColor);
		}
	}
}
