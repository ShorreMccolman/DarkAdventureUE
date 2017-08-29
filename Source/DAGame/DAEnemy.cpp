// Fill out your copyright notice in the Description page of Project Settings.

#include "DAEnemy.h"
#include "DAPlayer.h"
#include "DAPlayerAnimInstance.h"
#include "NavigationSystemHelpers.h"
#include "AI/Navigation/NavigationSystem.h"
#include "AI/Navigation/NavigationPath.h"

#include "Engine.h"


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
		Pursue(DeltaTime);
	}
}

void ADAEnemy::Pursue(float DeltaTime)
{
	UNavigationPath *tpath;
	UNavigationSystem* system = GetWorld()->GetNavigationSystem();
	tpath = system->FindPathToActorSynchronously(GetWorld(), GetActorLocation(), TargetEnemy);

	int Num = tpath->PathPoints.Num();

	FVector Targ;
	if (tpath->PathPoints.Num() > 1)
		Targ = tpath->PathPoints[1];
	else
		Targ = GetActorLocation();

	TargetDirection = Targ - GetActorLocation();
	TargetDirection.Normalize();

	FVector FacingVect = GetActorForwardVector();
	float angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(TargetDirection, FacingVect)));
	FVector Cross = FVector::CrossProduct(TargetDirection, FacingVect);

	if (angle > 1.f) {
		FVector Vect = GetActorRotation().Euler();
		if (Cross.Z < 0)
			Vect += FVector(0.f, 0.f, TurnRate * DeltaTime);
		else
			Vect += FVector(0.f, 0.f, -TurnRate * DeltaTime);
		FRotator Rot = FRotator::MakeFromEuler(Vect);
		SetActorRotation(Rot);
	}

	float distance = FVector::Distance(GetActorLocation(), TargetEnemy->GetActorLocation());
	if (distance > 150.f) {
		Speed += Acceleration * DeltaTime;

		// Using this to ease into lower max speed when releasing run
		if (Speed > 600.f) {
			Speed -= Decceleration * DeltaTime;
		}
	} else {
		Speed -= Decceleration * DeltaTime;
		Speed = FMath::Max(Speed, 0.f);
	}

	if (distance < 160.f)
		TryAttack();
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