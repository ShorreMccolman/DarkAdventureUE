// Fill out your copyright notice in the Description page of Project Settings.

#include "DAPlayerControllerPlay.h"
#include "Components/InputComponent.h"
#include "DAPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "DAMainGameMode.h"

void ADAPlayerControllerPlay::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("TargetX");
	InputComponent->BindAxis("TargetY");

	InputComponent->BindAction("Run", IE_Released, this, &ADAPlayerControllerPlay::ReleaseRun);
	InputComponent->BindAction("Lock", IE_Pressed, this, &ADAPlayerControllerPlay::PressLock);
}

void ADAPlayerControllerPlay::BeginPlay()
{
	Super::BeginPlay();

	DACharacter = Cast<ADAPlayer>(GetPawn());
	CameraBoom = DACharacter->GetCameraBoom();

	SetDAControlMode(EDAControlMode::DAControlMode_Play);
}

void ADAPlayerControllerPlay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DACharacter->RotateCameraBoom(GetInputAxisValue("TargetX") * DeltaTime * 100.f);
	DACharacter->ZoomCameraBoom(GetInputAxisValue("TargetY") * DeltaTime * 1000.f);

	const float ForwardValue = GetInputAxisValue("MoveY");
	const float RightValue = GetInputAxisValue("MoveX");

	FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f); // Clamped to length 1
	FRotator Rot = FRotator(0.f, CameraBoom->RelativeRotation.Yaw, 0.f);
	MoveDirection = Rot.RotateVector(MoveDirection);

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

void ADAPlayerControllerPlay::PressLock()
{
	DACharacter->ToggleLock();
}