// Fill out your copyright notice in the Description page of Project Settings.

#include "DAPlayerController.h"
#include "DAPlayer.h"

#include "Components/InputComponent.h"

void ADAPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveX");
	InputComponent->BindAxis("MoveY");

	InputComponent->BindAction("Run", IE_Pressed, this, &ADAPlayerController::PressRun);
	InputComponent->BindAction("Run", IE_Released, this, &ADAPlayerController::ReleaseRun);

	InputComponent->BindAction("Attack", IE_Pressed, this, &ADAPlayerController::PressAttack);

	InputComponent->BindAction("Lock", IE_Pressed, this, &ADAPlayerController::PressLock);

	InputComponent->BindAction("Test", IE_Pressed, this, &ADAPlayerController::PressTest);
}

void ADAPlayerController::BeginPlay()
{
	DACharacter = Cast<ADAPlayer>(GetPawn());

}


void ADAPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float ForwardValue = GetInputAxisValue("MoveY");
	const float RightValue = GetInputAxisValue("MoveX");

	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f); // Clamped to length 1

	DACharacter->SetInputDirection(MoveDirection);

	// Running Business
	bool ShouldRun = false;
	if (HoldingRun && RunBuffer == 0) {
		ShouldRun = true;
	}
	if (RunBuffer > 0)
		RunBuffer--;

	DACharacter->SetIsRunning(ShouldRun);

	if (DACharacter->GetCurrentSpeed() > 600.f) {
		
	}
}


void ADAPlayerController::PressAttack()
{
	DACharacter->TryAttack();
}

void ADAPlayerController::PressRun()
{
	HoldingRun = true;
	RunBuffer = 30;
}

void ADAPlayerController::ReleaseRun()
{
	HoldingRun = false;
	if (RunBuffer > 0) {
		DACharacter->TryRoll();
	}
}

void ADAPlayerController::PressTest()
{
	
}

void ADAPlayerController::PressLock()
{
	DACharacter->ToggleLock();
}