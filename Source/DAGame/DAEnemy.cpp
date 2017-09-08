// Fill out your copyright notice in the Description page of Project Settings.

#include "DAEnemy.h"
#include "DAPlayer.h"
#include "DAPlayerAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Components/WidgetComponent.h"
#include "DAWeaponBase.h"
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

	EquipWeapon("Blueprint'/Game/Weapons/BP_MutantClawWeapon.BP_MutantClawWeapon'", "LeftHandSocket");
}

// Called every frame
void ADAEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsDead)
		return;

	if (TargetEnemy) {
		float distance = FVector::Distance(GetActorLocation(), TargetEnemy->GetActorLocation());
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

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
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

	if (Animation) {
		Animation->SetupNextAnimation("Taunt", false);
	}
}

void ADAEnemy::LosePlayer(ADAPlayer* Player)
{
	TargetEnemy = nullptr;

	if (Animation) {
		Animation->SetupNextAnimation("Confuse", false);
	}
}