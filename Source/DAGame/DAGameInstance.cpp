// Fill out your copyright notice in the Description page of Project Settings.

#include "DAGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "DAPlayerSave.h"
#include "DAMasterSettings.h"

void UDAGameInstance::LoadMostRecentGame()
{
	UGameplayStatics::OpenLevel(this, "Main");
}

void UDAGameInstance::TryLoadGame(FString PlayerName)
{
	UDAMasterSettings* Settings = Cast<UDAMasterSettings>(UGameplayStatics::LoadGameFromSlot("Master", 0));
	if (!Settings) {
		UE_LOG(LogTemp, Warning, TEXT("Tried to load game but settings was not found!"))
		return;
	}

	if (Settings) {
		Settings->CurrentCharacterName = PlayerName;
		UGameplayStatics::SaveGameToSlot(Settings, "Master", 0);
	}
	UGameplayStatics::OpenLevel(this, "Main");
}

void UDAGameInstance::TryCreateNewGame(FString PlayerName, FDACharacterAttributes Attributes)
{
	CreatePlayerSave(PlayerName, Attributes);
	UGameplayStatics::OpenLevel(this, "Main");
}

void UDAGameInstance::CreatePlayerSave(FString PlayerName, FDACharacterAttributes Attributes)
{
	UDAPlayerSave* PlayerSave = Cast<UDAPlayerSave>(UGameplayStatics::CreateSaveGameObject(UDAPlayerSave::StaticClass()));
	PlayerSave->PlayerName = PlayerName;
	PlayerSave->Attributes = Attributes;
	PlayerSave->bIsNewPlayer = true;
	UGameplayStatics::SaveGameToSlot(PlayerSave, PlayerName, 0);

	UDAMasterSettings* Settings = Cast<UDAMasterSettings>(UGameplayStatics::LoadGameFromSlot("Master", 0));
	if (!Settings) {
		Settings = Cast<UDAMasterSettings>(UGameplayStatics::CreateSaveGameObject(UDAMasterSettings::StaticClass()));
		UE_LOG(LogTemp, Warning, TEXT("Created new master save file!"))
	}

	if (Settings) {
		Settings->CharacterNames.AddUnique(PlayerName);
		Settings->CurrentCharacterName = PlayerName;
		Settings->bHasCharacter = true;
		UGameplayStatics::SaveGameToSlot(Settings, "Master", 0);
	}
}

UDAPlayerSave* UDAGameInstance::LoadCurrentPlayerSave()
{
	FString CurrentName;
	UDAMasterSettings* Settings = Cast<UDAMasterSettings>(UGameplayStatics::LoadGameFromSlot("Master", 0));
	if (Settings) {
		UDAPlayerSave* PlayerSave = Cast<UDAPlayerSave>(UGameplayStatics::CreateSaveGameObject(UDAPlayerSave::StaticClass()));
		PlayerSave = Cast<UDAPlayerSave>(UGameplayStatics::LoadGameFromSlot(Settings->CurrentCharacterName, 0));

		if (!PlayerSave) {
			UE_LOG(LogTemp, Warning, TEXT("Could not find player save"))
				return nullptr;
		}
		return PlayerSave;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Could not find master settings"))
	}
	return nullptr;
}