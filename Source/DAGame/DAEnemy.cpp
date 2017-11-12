// Fill out your copyright notice in the Description page of Project Settings.

#include "DAEnemy.h"
#include "DAPlayer.h"
#include "DAPlayerAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "DAWeaponBase.h"
#include "DAGeneratedAttributes.h"
#include "DAMainGameMode.h"
#include "DAPlayerAnimInstance.h"


// Sets default values
ADAEnemy::ADAEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Target = CreateDefaultSubobject<UWidgetComponent>(TEXT("Target"));
	Target->SetupAttachment(GetCapsuleComponent());

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBar->SetupAttachment(GetCapsuleComponent());

	FGuid guid = FGuid::NewGuid();
	InstanceID = guid.ToString();
}

// Called when the game starts or when spawned
void ADAEnemy::BeginPlay()
{
	Super::BeginPlay();
	OriginLocation = GetActorLocation();
}

// Called every frame
void ADAEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsDead)
		return;

	if (TargetEnemy) 
	{
		float distance = FVector::Distance(GetActorLocation(), TargetEnemy->GetActorLocation());
		Pursue(distance, DeltaTime);

		if (distance < 160.f && distance > 140.f)
			TryAttack();
	}
	else {
		HoldPosition(DeltaTime);
	}
}

void ADAEnemy::Init(FName RegionID, bool IsDead)
{
	bIsDead = IsDead;
	ShowDetails(false);
	this->RegionID = RegionID;
	EquipWeapon("Claw", "LeftHandSocket");

	GeneratedAttributes = NewObject<UDAGeneratedAttributes>(UDAGeneratedAttributes::StaticClass());
	GeneratedAttributes->UpdateWithEnemyCharacter(*this);
	Vitals.MaxHealth = GeneratedAttributes->MaxHealth;
	Vitals.CurHealth = Vitals.MaxHealth;
	Vitals.MaxStamina = GeneratedAttributes->MaxStamina;
	Vitals.CurStamina = Vitals.MaxStamina;

	GetCapsuleComponent()->SetCollisionEnabled(IsDead ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryAndPhysics);

	if (Animation) {
		if (IsDead) {
			Animation->QuickDeath();
		}
		else {
			Animation->ResetCharacter();
		}
	}
}

void ADAEnemy::Uninit()
{
	if (Weapon) {
		Weapon->Destroy();
	}
}

void ADAEnemy::Reset()
{
	Super::Reset();

}

void ADAEnemy::ShowTarget(bool ShouldTarget)
{
	Super::ShowTarget(ShouldTarget);

	Target->SetVisibility(ShouldTarget);
}

void ADAEnemy::TriggerIncomingDamage()
{
	DamageLabelNumber += IncomingDamage;
	Super::TriggerIncomingDamage();

	ShowDetails(true);
	GetWorldTimerManager().ClearTimer(DamageLabelTimerHandle);
	GetWorldTimerManager().SetTimer(DamageLabelTimerHandle, this, &ADAEnemy::ClearDamageLabelNumer, 3.f, false);
}

void ADAEnemy::ClearDamageLabelNumer()
{
	DamageLabelNumber = 0;
	ShowDetails(false);

	GetWorldTimerManager().ClearTimer(DamageLabelTimerHandle);
}

void ADAEnemy::OnCharacterDeath()
{
	Super::OnCharacterDeath();

	TArray<FDALootDrop> Drops = RollForLootDrops(LootRolls);
	for (auto Drop : Drops) {
		SpawnPickup(Drop);
	}

	ADAPlayer* Player = Cast<ADAPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player) {
		Player->GainSouls(EnemyAttributes.SoulReward);
	}

	ADAMainGameMode* Mode = Cast<ADAMainGameMode>(GetWorld()->GetAuthGameMode());
	if (Mode) {
		Mode->SlayEnemy(RegionID, InstanceID);
	}
}

void ADAEnemy::ShowDetails(bool ShouldShow)
{
	Super::ShowDetails(ShouldShow);

	HealthBar->SetVisibility(ShouldShow);
	UpdateDetailsWidget();
}

void ADAEnemy::NoticePlayer(ADAPlayer* Player)
{
	TargetEnemy = Player;

	if (Animation) 
	{
		Animation->SetupNextAnimation("Taunt", false);
	}
}

void ADAEnemy::LosePlayer(ADAPlayer* Player)
{
	TargetEnemy = nullptr;

	if (Animation) 
	{
		Animation->SetupNextAnimation("Confuse", false);
	}
}

TArray<FDALootDrop> ADAEnemy::RollForLootDrops(const TArray<FDALootRolls>& Rolls) const
{
	TArray<FDALootDrop> Drops;
	for (auto Roll : Rolls) 
	{
		if (FMath::FRand() <= Roll.ChanceToDrop) 
		{
			int Total = 0;
			for (auto Drop : Roll.Drops) 
			{
				Total += Drop.Weight;
			}

			int Rand = FMath::RandHelper(Total);

			int Current = 0;
			for (auto Drop : Roll.Drops) 
			{
				if (Rand <= Current)
				{
					Drops.Add(Drop);
					break;
				}
				else {
					Current += Drop.Weight;
				}
			}
		}
	}
	return Drops;
}