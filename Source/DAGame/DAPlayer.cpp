// Fill out your copyright notice in the Description page of Project Settings.

#include "DAPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DAPlayerAnimInstance.h"


// Sets default values
ADAPlayer::ADAPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WalkSpeed = 600.f;
	Acceleration = 800.f;
	Decceleration = 1200.f;
	TurnRate = 100.f;
}

// Called when the game starts or when spawned
void ADAPlayer::BeginPlay()
{
	Super::BeginPlay();

	TargetDirection = GetActorForwardVector();
}

// Called every frame
void ADAPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Locked)
		LockedMotion(DeltaTime);
	else
		StandardMotion(DeltaTime);
}
