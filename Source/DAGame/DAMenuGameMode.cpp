// Fill out your copyright notice in the Description page of Project Settings.

#include "DAMenuGameMode.h"
#include "DAMasterSettings.h"
#include "Kismet/GameplayStatics.h"


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

bool ADAMenuGameMode::HasSaveGame()
{
	UDAMasterSettings* Settings = Cast<UDAMasterSettings>(UGameplayStatics::LoadGameFromSlot("Master", 0));
	if (!Settings) {
		UE_LOG(LogTemp, Warning, TEXT("Tried to load game but settings was not found!"))
		return false;
	}

	if (Settings) {
		return Settings->bHasCharacter;
	}

	return false;
}