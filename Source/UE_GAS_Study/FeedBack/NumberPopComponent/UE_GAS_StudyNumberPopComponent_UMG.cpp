#include "UE_GAS_StudyNumberPopComponent_UMG.h"

#include "UE_GAS_StudyNumberPopActor.h"

UUE_GAS_StudyNumberPopComponent_UMG::UUE_GAS_StudyNumberPopComponent_UMG(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UUE_GAS_StudyNumberPopComponent_UMG::AddNumberPop(const FUE_GAS_StudyNumberPopRequest& NewRequest)
{
	Super::AddNumberPop(NewRequest);

	if (APlayerController*PC = GetOwner<APlayerController>())
	{
		if (!PC->IsLocalController())
		{
			return;
		}
	}
	
	FTransform CameraTransform;
	FVector NumberLocation(NewRequest.WorldLocation);
	if (APlayerController* PC = GetOwner<APlayerController>())
	{
		if (APlayerCameraManager* PlayerCameraManager = PC->PlayerCameraManager)
		{
			CameraTransform = FTransform(PlayerCameraManager->GetCameraRotation(),PlayerCameraManager->GetCameraLocation());
			
			FVector LocationOffset(ForceInitToZero);
			
			const float RandomMagnitude = 5.0f;
			LocationOffset += FMath::RandPointInBox(FBox(FVector(-RandomMagnitude),FVector(RandomMagnitude)));
			
			NumberLocation += LocationOffset;
		}
	}

	if (UWorld* LocalWorld = GetWorld())
	{
		AUE_GAS_StudyNumberPopActor* PopActor = LocalWorld->SpawnActor<AUE_GAS_StudyNumberPopActor>(NumPopActorClass,NewRequest.WorldLocation,FRotator::ZeroRotator);
		
		PopActor->UpdateNum(FText::FromString(FString::FromInt(NewRequest.NumberToDisplay)));
		PopActor->UpdateNumColor(NewRequest.ColorToDisplay);
	}
}
