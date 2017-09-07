// Fill out your copyright notice in the Description page of Project Settings.

#include "DAMenuGameMode.h"


ADAMenuGameMode::ADAMenuGameMode()
{

}

void ADAMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	AddMenu(MainWidgetClass);
}

void ADAMenuGameMode::StartButton()
{
	AcceptCurrent();
}