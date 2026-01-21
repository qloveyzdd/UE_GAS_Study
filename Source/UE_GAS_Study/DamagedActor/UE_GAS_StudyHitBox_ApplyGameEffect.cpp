#include "UE_GAS_StudyHitBox_ApplyGameEffect.h"

#include "AbilitySystemComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UE_GAS_Study/Character/UE_GAS_StudyCharacterBase.h"

AUE_GAS_StudyHitBox_ApplyGameEffect::AUE_GAS_StudyHitBox_ApplyGameEffect(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	HitCollisionRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CollisionRootComponent"));
	RootComponent = HitCollisionRootComponent;

	HitDamage = CreateDefaultSubobject<UBoxComponent>(TEXT("HitDamage"));
	HitDamage->SetupAttachment(RootComponent);

	InitialLifeSpan = 4.0f;
	bNetLoadOnClient = true;
	bReplicates = true;
	SetReplicatingMovement(true);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->MaxSpeed = 2000.0f;
	ProjectileMovement->InitialSpeed = 1600.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->SetUpdatedComponent(RootComponent);
	ProjectileMovement->SetIsReplicated(true);

	HitCollisionType = EGAS_StudyHitCollisionType::HitCollisionType_Short_Range_Attack;
}

void AUE_GAS_StudyHitBox_ApplyGameEffect::BeginPlay()
{
	Super::BeginPlay();

	if (UPrimitiveComponent* InHitComponent = GetHitDamage())
	{
		InHitComponent->SetHiddenInGame(true);
		InHitComponent->OnComponentBeginOverlap.AddDynamic(this, &AUE_GAS_StudyHitBox_ApplyGameEffect::HandleDamage);
	}
}

void AUE_GAS_StudyHitBox_ApplyGameEffect::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AUE_GAS_StudyHitBox_ApplyGameEffect::PreInitCollision(AActor* InMyInstigator)
{
	if (!InMyInstigator)
	{
		return;
	}

	FVector ShootDirection = InMyInstigator->GetActorRotation().Vector();
	switch (HitCollisionType)
	{
	case EGAS_StudyHitCollisionType::HitCollisionType_Short_Range_Attack:
		ProjectileMovement->MaxSpeed = 0.0f;
		ProjectileMovement->InitialSpeed = 0.0f;
		ProjectileMovement->ProjectileGravityScale = 0.0f;
		break;
	case EGAS_StudyHitCollisionType::HitCollisionType_Direct_Line:
		RootComponent->SetWorldRotation(FRotator::ZeroRotator);
		ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
		break;
	default:
		break;
	}
}

void AUE_GAS_StudyHitBox_ApplyGameEffect::HandleDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                                       bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetInstigator() != OtherActor)
	{
		if (AUE_GAS_StudyCharacterBase* InTarget = Cast<AUE_GAS_StudyCharacterBase>(OtherActor))
		{
			if (!InTarget->IsNetMode(NM_Client))
			{
				if (IsExist(InTarget))
				{
					return;
				}

				if (UAbilitySystemComponent* InAbilitySystemComponent = InTarget->GetAbilitySystemComponent())
				{
					FGameplayEffectContextHandle EffectContext = InAbilitySystemComponent->MakeEffectContext();
					
					EffectContext.AddInstigator(GetInstigator(),this);
					
					EffectContext.AddSourceObject(InTarget);
					
					FGameplayEffectSpecHandle EffectSpecHandle = InAbilitySystemComponent->MakeOutgoingSpec(EffectClass,1,EffectContext);

					if (EffectSpecHandle.IsValid())
					{
						InAbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(),InAbilitySystemComponent);
					}
					
					AttackedTarget.AddUnique(InTarget);
				}
			}
		}
	}
}

UPrimitiveComponent* AUE_GAS_StudyHitBox_ApplyGameEffect::GetHitDamage()
{
	return HitDamage;
}

void AUE_GAS_StudyHitBox_ApplyGameEffect::SetHitDamageRelativePosition(const FVector& InNewPostion)
{
	if (UPrimitiveComponent* InHitComponent = GetHitDamage())
	{
		InHitComponent->SetRelativeLocation(InNewPostion);
	}
}

void AUE_GAS_StudyHitBox_ApplyGameEffect::SetBoxExtent(const FVector& InNewBoxExtent)
{
	HitDamage->SetBoxExtent(InNewBoxExtent);
}

void AUE_GAS_StudyHitBox_ApplyGameEffect::SetGameplayEffect(TSubclassOf<UGameplayEffect>& InGE)
{
	EffectClass = InGE;
}

bool AUE_GAS_StudyHitBox_ApplyGameEffect::IsExist(class AUE_GAS_StudyCharacterBase* InNewTarget) const
{
	for (auto& Tmp : AttackedTarget)
	{
		if (Tmp.IsValid())
		{
			if (Tmp == InNewTarget)
			{
				return true;
			}
		}
	}
	return false;
}
