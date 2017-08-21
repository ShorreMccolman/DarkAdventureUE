// Fill out your copyright notice in the Description page of Project Settings.

#include "DAPlayerController.h"
#include "DAPlayer.h"



void ADAPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ADAPlayer* Player = Cast<ADAPlayer>(GetPawn());
	if (Player->GetCurrentSpeed() > 600.f) {

	}

}