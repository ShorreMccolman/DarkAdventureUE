// Fill out your copyright notice in the Description page of Project Settings.

#include "DAPlayerController.h"
#include "DAPlayer.h"
#include "Components/InputComponent.h"
#include "DAGameMode.h"

void ADAPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveX");
	InputComponent->BindAxis("MoveY");

	InputComponent->BindAction("Start", IE_Pressed, this, &ADAPlayerController::PressStart);

	InputComponent->BindAction("Attack", IE_Pressed, this, &ADAPlayerController::PressRightButton);
	InputComponent->BindAction("StrongAttack", IE_Pressed, this, &ADAPlayerController::PressRightTrigger);
	InputComponent->BindAction("LeftAttack", IE_Pressed, this, &ADAPlayerController::PressLeftButton);
	InputComponent->BindAction("LeftStrongAttack", IE_Pressed, this, &ADAPlayerController::PressLeftTrigger);

	InputComponent->BindAction("Interact", IE_Pressed, this, &ADAPlayerController::PressInteract);
	InputComponent->BindAction("Run", IE_Pressed, this, &ADAPlayerController::PressRun);
	InputComponent->BindAction("Use", IE_Pressed, this, &ADAPlayerController::PressUse);
	InputComponent->BindAction("Heal", IE_Pressed, this, &ADAPlayerController::PressHeal);

	InputComponent->BindAction("DUP", IE_Pressed, this, &ADAPlayerController::PressDUp);
	InputComponent->BindAction("DRIGHT", IE_Pressed, this, &ADAPlayerController::PressDRight);
	InputComponent->BindAction("DDOWN", IE_Pressed, this, &ADAPlayerController::PressDDown);
	InputComponent->BindAction("DLEFT", IE_Pressed, this, &ADAPlayerController::PressDLeft);
}

void ADAPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<ADAGameMode>(GetWorld()->GetAuthGameMode());
}


void ADAPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
		GameMode->StartButton();
		break;
	case EDAControlMode::DAControlMode_FullMenu:
	case EDAControlMode::DAControlMode_PlayMenu:
		GameMode->CancelCurrent();
		break;
	default:
		break;
	}
}

void ADAPlayerController::PressRightButton()
{
	switch (ControlMode)
	{
	case EDAControlMode::DAControlMode_Play:
		DACharacter->TryAttack();
		break;
	case EDAControlMode::DAControlMode_FullMenu:
	case EDAControlMode::DAControlMode_PlayMenu:
		GameMode->RightButton();
		break;
	default:
		break;
	}
}

void ADAPlayerController::PressRightTrigger()
{
	switch (ControlMode)
	{
	case EDAControlMode::DAControlMode_Play:
		DACharacter->TryStrongAttack();
		break;
	case EDAControlMode::DAControlMode_FullMenu:
	case EDAControlMode::DAControlMode_PlayMenu:
		break;
	default:
		break;
	}
}

void ADAPlayerController::PressLeftButton()
{
	switch (ControlMode)
	{
	case EDAControlMode::DAControlMode_Play:
		
		break;
	case EDAControlMode::DAControlMode_FullMenu:
	case EDAControlMode::DAControlMode_PlayMenu:
		GameMode->LeftButton();
		break;
	default:
		break;
	}
}

void ADAPlayerController::PressLeftTrigger()
{
	switch (ControlMode)
	{
	case EDAControlMode::DAControlMode_Play:
		
		break;
	case EDAControlMode::DAControlMode_FullMenu:
	case EDAControlMode::DAControlMode_PlayMenu:
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
	switch (ControlMode)
	{
	case EDAControlMode::DAControlMode_Play:
		DACharacter->TryUse();
		break;
	case EDAControlMode::DAControlMode_FullMenu:
	case EDAControlMode::DAControlMode_PlayMenu:
		GameMode->DeleteCurrent();
		break;
	default:
		break;
	}
}

void ADAPlayerController::PressHeal()
{
	switch (ControlMode)
	{
	case EDAControlMode::DAControlMode_Play:
		DACharacter->TryHeal();
		break;
	case EDAControlMode::DAControlMode_FullMenu:
	case EDAControlMode::DAControlMode_PlayMenu:
		GameMode->ToggleFace();
		break;
	default:
		break;
	}
}

void ADAPlayerController::PressDUp()
{
	switch (ControlMode)
	{
	case EDAControlMode::DAControlMode_Play:
		DACharacter->TryConsumable(EDAEquipmentSlot::EDAEquipmentSlot_Consumable1);
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
		DACharacter->TryConsumable(EDAEquipmentSlot::EDAEquipmentSlot_Consumable4);
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
		DACharacter->TryConsumable(EDAEquipmentSlot::EDAEquipmentSlot_Consumable2);
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
		DACharacter->TryConsumable(EDAEquipmentSlot::EDAEquipmentSlot_Consumable3);
		break;
	case EDAControlMode::DAControlMode_FullMenu:
	case EDAControlMode::DAControlMode_PlayMenu:
		GameMode->NavigateCurrent(EDAInputDirection::DAInputDirection_Left);
		break;
	default:
		break;
	}
}