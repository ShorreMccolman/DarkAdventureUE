// Fill out your copyright notice in the Description page of Project Settings.

#include "DAPlayerControllerPlay.h"
#include "Components/InputComponent.h"
#include "DAPlayer.h"
#include "DAMainGameMode.h"

void ADAPlayerControllerPlay::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("Run", IE_Released, this, &ADAPlayerControllerPlay::ReleaseRun);
	InputComponent->BindAction("Heal", IE_Pressed, this, &ADAPlayerControllerPlay::PressHeal);

	InputComponent->BindAction("Attack", IE_Pressed, this, &ADAPlayerControllerPlay::PressAttack);
	InputComponent->BindAction("StrongAttack", IE_Pressed, this, &ADAPlayerControllerPlay::PressStrongAttack);

	InputComponent->BindAction("Lock", IE_Pressed, this, &ADAPlayerControllerPlay::PressLock);
}

void ADAPlayerControllerPlay::BeginPlay()
{
	Super::BeginPlay();

	DACharacter = Cast<ADAPlayer>(GetPawn());
	SetDAControlMode(EDAControlMode::DAControlMode_Play);
}


void ADAPlayerControllerPlay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float ForwardValue = GetInputAxisValue("MoveY");
	const float RightValue = GetInputAxisValue("MoveX");

	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f); // Clamped to length 1

	// Running Business
	bool ShouldRun = false;
	if (HoldingRun && RunBuffer == 0) {
		ShouldRun = true;
	}
	if (RunBuffer > 0)
		RunBuffer--;

	if (DACharacter) {
		if (ShouldRun) {
			DACharacter->ConsumeStamina(8.f * DeltaTime);
			if (DACharacter->GetCurrentStaminaPercent() == 0.f)
				HoldingRun = false;
		}

		DACharacter->SetInputDirection(MoveDirection);
		DACharacter->SetIsRunning(ShouldRun);
	}
}

void ADAPlayerControllerPlay::PressAttack()
{
	DACharacter->TryAttack();
}

void ADAPlayerControllerPlay::PressStrongAttack()
{
	DACharacter->TryStrongAttack();
}

void ADAPlayerControllerPlay::PressLock()
{
	DACharacter->ToggleLock();
}