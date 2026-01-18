// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "UE_GAS_StudyPlayerController.generated.h"

UCLASS(Config=Game, Meta = (ShortTooltip = "The base player controller class used by this project."))
class UE_GAS_STUDY_API AUE_GAS_StudyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="GAS Study|DanamgNum",meta = (AllowPrivateAccess="true"))
	TObjectPtr<class UUE_GAS_StudyNumberPopComponent_UMG> NumberPopComponent;

public:
	AUE_GAS_StudyPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//当有输入操作时调用该方法
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

public:
	UFUNCTION(BlueprintCallable, Category="UE_GAS_Study|PlayerController")
	class UUE_GAS_StudyAbilitySystemComponent* GetGASStudyAbilitySystemComponent() const;

	UFUNCTION(BlueprintCallable, Category="UE_GAS_Study|PlayerController")
	class AUE_GAS_StudyHUD* GetGASStudyHUD() const;

	UFUNCTION(BlueprintCallable, Category="UE_GAS_Study|PlayerController")
	class AUE_GAS_StudyPlayerState* GetGASStudyPlayerState() const;
	
	UFUNCTION(BlueprintCallable, Category="UE_GAS_Study|PlayerController")
	class UUE_GAS_StudyNumberPopComponent* GetGASStudyNumberPopComponent() const;
};
