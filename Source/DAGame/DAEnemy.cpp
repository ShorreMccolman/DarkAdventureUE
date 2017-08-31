// Fill out your copyright notice in the Description page of Project Settings.

#include "DAEnemy.h"
#include "DAPlayer.h"
#include "DAPlayerAnimInstance.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ADAEnemy::ADAEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADAEnemy::BeginPlay()
{
	Super::BeginPlay();
	
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

void ADAEnemy::OnCharacterDeath()
{
	Super::OnCharacterDeath();

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
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