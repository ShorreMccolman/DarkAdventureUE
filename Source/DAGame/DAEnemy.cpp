// Fill out your copyright notice in the Description page of Project Settings.

#include "DAEnemy.h"
#include "DAPlayer.h"
#include "DAPlayerAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Components/WidgetComponent.h"
#include "DAWeaponBase.h"
#include "DAGeneratedAttributes.h"
#include "Animation/AnimInstance.h"


// Sets default values
ADAEnemy::ADAEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Target = CreateDefaultSubobject<UWidgetComponent>(TEXT("Target"));
	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
}

// Called when the game starts or when spawned
void ADAEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	Origin = GetActorLocation();
	ShowDetails(false);

	EquipWeapon("Claw", "LeftHandSocket");
	GeneratedAttributes = NewObject<UDAGeneratedAttributes>(UDAGeneratedAttributes::StaticClass());
	GeneratedAttributes->UpdateWithEnemyCharacter(*this);
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
		UE_LOG(LogTemp, Warning, TEXT("Distance is %f"), distance)
		Pursue(distance, DeltaTime);

		if (distance < 160.f && distance > 140.f)
			TryAttack();
	}
	else {
		HoldPosition(DeltaTime);
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
	UE_LOG(LogTemp, Warning, TEXT("Noticed Player"))

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