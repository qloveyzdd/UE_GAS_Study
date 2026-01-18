#include "UI_DamageNum.h"

#include "Components/TextBlock.h"

void UUI_DamageNum::NativeConstruct()
{
	Super::NativeConstruct();
	
	PlayWidgetAnim(TEXT("FadeAnimation"));
}

void UUI_DamageNum::UpdateNum(const FText& InText)
{
	if (NumText)
	{
		NumText->SetText(InText);
	}
}

void UUI_DamageNum::UpdateNumColor(const FLinearColor& InColor)
{
	if (NumText)
	{
		NumText->SetColorAndOpacity(InColor);
	}
}
