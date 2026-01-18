#include "UE_GAS_StudyHitBox.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Components/BoxComponent.h"
#include "UE_GAS_Study/AbilitySystem/Abilities/UE_GAS_StudyGameplayAbility_Death.h"
#include "UE_GAS_Study/Character/UE_GAS_StudyCharacterBase.h"

AUE_GAS_StudyHitBox::AUE_GAS_StudyHitBox(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	HitCollisionRootComponent = CreateDefaultSubobject<USceneComponent>("HitCollisionRootComponent");
	RootComponent = HitCollisionRootComponent;

	HitDamage = CreateDefaultSubobject<UBoxComponent>("HitDamage");
	HitDamage->SetupAttachment(RootComponent);

	InitialLifeSpan = 4.0f;
	bNetLoadOnClient = false;
	bReplicates = false;
}

void AUE_GAS_StudyHitBox::HandleDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                       const FHitResult& SweepResult)
{
	if (GetInstigator() != OtherActor)
	{
		if (AUE_GAS_StudyCharacterBase* InPawn = Cast<AUE_GAS_StudyCharacterBase>(GetInstigator()))
		{
			if (AUE_GAS_StudyCharacterBase* InTarget = Cast<AUE_GAS_StudyCharacterBase>(OtherActor))
			{
				if (!InPawn->IsNetMode(NM_Client))
				{
					FGameplayEventData EventData;
					EventData.Instigator = GetInstigator();
					EventData.Target = InTarget;

					if (IsExist(InTarget))
					{
						return;
					}

					if (!BuffsTags.IsEmpty())
					{
						for (auto& Tmp : BuffsTags)
						{
							UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
								GetInstigator(), Tmp.Last(), EventData);
						}
					}
					AttackedTarget.AddUnique(InTarget);
				}
			}
		}
	}
}

UPrimitiveComponent* AUE_GAS_StudyHitBox::GetHitDamage()
{
	return HitDamage;
}

void AUE_GAS_StudyHitBox::SetHitDamageRelativePosition(const FVector& InNewPostion)
{
	if (UPrimitiveComponent* InHitComponent = GetHitDamage())
	{
		InHitComponent->SetRelativeLocation(InNewPostion);
	}
}

void AUE_GAS_StudyHitBox::SetBoxExtent(const FVector& InNewBoxExtent)
{
	HitDamage->SetBoxExtent(InNewBoxExtent);
}

void AUE_GAS_StudyHitBox::SetBuffs(const TArray<struct FGameplayTagContainer>& InBuffs)
{
	BuffsTags = InBuffs;
}

bool AUE_GAS_StudyHitBox::IsExist(class AUE_GAS_StudyCharacterBase* InNewTaget) const
{
	for (auto& Tmp : AttackedTarget)
	{
		if (Tmp.IsValid())
		{
			if (Tmp == InNewTaget)
			{
				return true;
			}
		}
	}
	return false;
}

void AUE_GAS_StudyHitBox::BeginPlay()
{
	Super::BeginPlay();

	if (UPrimitiveComponent* InHitComponent = GetHitDamage())
	{
		InHitComponent->SetHiddenInGame(true);
		InHitComponent->OnComponentBeginOverlap.AddDynamic(this, &AUE_GAS_StudyHitBox::HandleDamage);
	}
}

void AUE_GAS_StudyHitBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
