// Fill out your copyright notice in the Description page of Project Settings.

#include "DAPlayerControllerMenu.h"

void ADAPlayerControllerMenu::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

}

void ADAPlayerControllerMenu::BeginPlay()
{
	Super::BeginPlay();

	SetDAControlMode(EDAControlMode::DAControlMode_FullMenu);
}


void ADAPlayerControllerMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float ForwardValue = GetInputAxisValue("MoveY");
	const float RightValue = GetInputAxisValue("MoveX");

}