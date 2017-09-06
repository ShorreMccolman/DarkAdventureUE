// Fill out your copyright notice in the Description page of Project Settings.

#include "DAPlayerController.h"
#include "DAPlayer.h"
#include "Components/InputComponent.h"
#include "DAMainGameMode.h"

void ADAPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveX");
	InputComponent->BindAxis("MoveY");

	InputComponent->BindAction("Start", IE_Pressed, this, &ADAPlayerController::PressStart);

	InputComponent->BindAction("Interact", IE_Pressed, this, &ADAPlayerController::PressInteract);
	InputComponent->BindAction("Run", IE_Pressed, this, &ADAPlayerController::PressRun);
	InputComponent->BindAction("Run", IE_Released, this, &ADAPlayerController::ReleaseRun);
	InputComponent->BindAction("Heal", IE_Pressed, this, &ADAPlayerController::PressHeal);
	InputComponent->BindAction("Use", IE_Pressed, this, &ADAPlayerController::PressUse);

	InputComponent->BindAction("Attack", IE_Pressed, this, &ADAPlayerController::PressAttack);
	InputComponent->BindAction("StrongAttack", IE_Pressed, this, &ADAPlayerController::PressStrongAttack);

	InputComponent->BindAction("Lock", IE_Pressed, this, &ADAPlayerController::PressLock);
	InputComponent->BindAction("DUP", IE_Pressed, this, &ADAPlayerController::PressDUp);
	InputComponent->BindAction("DRIGHT", IE_Pressed, this, &ADAPlayerController::PressDRight);
	InputComponent->BindAction("DDOWN", IE_Pressed, this, &ADAPlayerController::PressDDown);
	InputComponent->BindAction("DLEFT", IE_Pressed, this, &ADAPlayerController::PressDLeft);
}

void ADAPlayerController::BeginPlay()
{
	DACharacter = Cast<ADAPlayer>(GetPawn());
	GameMode = Cast<ADAMainGameMode>(GetWorld()->GetAuthGameMode());
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

	if (ShouldRun) {
		DACharacter->ConsumeStamina(8.f * DeltaTime);
		if (DACharacter->GetCurrentStaminaPercent() == 0.f)
			HoldingRun = false;
	}

	DACharacter->SetIsRunning(ShouldRun);
}

void ADAPlayerController::SetDAControlMode(EDAControlMode Mode)
{
	ControlMode = Mode;
}

void ADAPlayerController::PressStart()
{
	switch (ControlMode)
	{
	case EDAControlMode::DAControlMode_Play:
		GameMode->OpenStartMenu();
		break;
	case EDAControlMode::DAControlMode_FullMenu:
	case EDAControlMode::DAControlMode_PlayMenu:
		GameMode->CancelCurrent();
		break;
	default:
		break;
	}
}

void ADAPlayerController::PressInteract()
{
	switch (ControlMode)
	{
	case EDAControlMode::DAControlMode_Play:
		DACharacter->TryInteract();
		break;
	case EDAControlMode::DAControlMode_FullMenu:
	case EDAControlMode::DAControlMode_PlayMenu:
		GameMode->AcceptCurrent();
		break;
	default:
		break;
	}
}

void ADAPlayerController::PressAttack()
{
	DACharacter->TryAttack();
}

void ADAPlayerController::PressStrongAttack()
{
	DACharacter->TryStrongAttack();
}

void ADAPlayerController::PressRun()
{
	switch (ControlMode)
	{
	case EDAControlMode::DAControlMode_Play:
		HoldingRun = true;
		RunBuffer = 30;
		break;
	case EDAControlMode::DAControlMode_FullMenu:
	case EDAControlMode::DAControlMode_PlayMenu:
		GameMode->CancelCurrent();
		break;
	default:
		break;
	}
}

void ADAPlayerController::ReleaseRun()
{
	HoldingRun = false;
	switch (ControlMode)
	{
	case EDAControlMode::DAControlMode_Play:
		if (RunBuffer > 0) {
			DACharacter->TryRoll();
		}
		break;
	case EDAControlMode::DAControlMode_FullMenu:
	case EDAControlMode::DAControlMode_PlayMenu:
		break;
	default:
		break;
	}
}

void ADAPlayerController::PressUse()
{

}

void ADAPlayerController::PressHeal()
{
	
}

void ADAPlayerController::PressLock()
{
	DACharacter->ToggleLock();
}

void ADAPlayerController::PressDUp()
{
	switch (ControlMode)
	{
	case EDAControlMode::DAControlMode_Play:
		break;
	case EDAControlMode::DAControlMode_FullMenu:
	case EDAControlMode::DAControlMode_PlayMenu:
		GameMode->NavigateCurrent(EDAInputDirection::DAInputDirection_Up);
		break;
	default:
		break;
	}
}

void ADAPlayerController::PressDRight()
{
	switch (ControlMode)
	{
	case EDAControlMode::DAControlMode_Play:
		break;
	case EDAControlMode::DAControlMode_FullMenu:
	case EDAControlMode::DAControlMode_PlayMenu:
		GameMode->NavigateCurrent(EDAInputDirection::DAInputDirection_Right);
		break;
	default:
		break;
	}
}

void ADAPlayerController::PressDDown()
{
	switch (ControlMode)
	{
	case EDAControlMode::DAControlMode_Play:
		break;
	case EDAControlMode::DAControlMode_FullMenu:
	case EDAControlMode::DAControlMode_PlayMenu:
		GameMode->NavigateCurrent(EDAInputDirection::DAInputDirection_Down);
		break;
	default:
		break;
	}
}

void ADAPlayerController::PressDLeft()
{
	switch (ControlMode)
	{
	case EDAControlMode::DAControlMode_Play:
		break;
	case EDAControlMode::DAControlMode_FullMenu:
	case EDAControlMode::DAControlMode_PlayMenu:
		GameMode->NavigateCurrent(EDAInputDirection::DAInputDirection_Left);
		break;
	default:
		break;
	}
}