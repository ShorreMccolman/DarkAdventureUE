// Fill out your copyright notice in the Description page of Project Settings.

#include "DAEnemy.h"


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

	if (TargetEnemy && !IsDead) {
		TargetDirection = TargetEnemy->GetActorLocation() - GetActorLocation();
		FaceRotation(TargetDirection.Rotation());

		float distance = TargetDirection.Size();
		if (distance < 400.f) {
			Speed += Acceleration * DeltaTime;

			// Using this to ease into lower max speed when releasing run
			if (Speed > 600.f) {
				Speed -= Decceleration * DeltaTime;
			}

			if(distance < 150.f)
				TryAttack();
		}
		else {
			Speed -= Decceleration * DeltaTime;
			Speed = FMath::Max(Speed, 0.f);
		}
	}
}

