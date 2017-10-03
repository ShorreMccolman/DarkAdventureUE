// Fill out your copyright notice in the Description page of Project Settings.

#include "DAGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "DAPlayerSave.h"
#include "DAMasterSettings.h"

void UDAGameInstance::InitSettings()
{
	USaveGame* Master = UGameplayStatics::LoadGameFromSlot("Master", 0);
	if (!Master) {
		Settings = Cast<UDAMasterSettings>(UGameplayStatics::CreateSaveGameObject(UDAMasterSettings::StaticClass()));
		UE_LOG(LogTemp, Warning, TEXT("Created new master save file!"))
		UGameplayStatics::SaveGameToSlot(Settings, "Master", 0);
	}
	else {
		Settings = Cast<UDAMasterSettings>(Master);
	}
}

const UDAMasterSettings* UDAGameInstance::GetSettings()
{
	if (!Settings)
		InitSettings();

	return Settings;
}

void UDAGameInstance::LoadMostRecentGame()
{
	UGameplayStatics::OpenLevel(this, "Main");
}

void UDAGameInstance::TryLoadGame(FString PlayerName)
{
	if (!Settings) {
		InitSettings();
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
	PlayerSave = Cast<UDAPlayerSave>(UGameplayStatics::CreateSaveGameObject(UDAPlayerSave::StaticClass()));
	PlayerSave->PlayerName = PlayerName;
	PlayerSave->Attributes = Attributes;
	PlayerSave->bIsNewPlayer = true;
	UGameplayStatics::SaveGameToSlot(PlayerSave, PlayerName, 0);

	if (!Settings) {
		InitSettings();
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
	if (!Settings) {
		InitSettings();
	}

	if (Settings) {
		PlayerSave = Cast<UDAPlayerSave>(UGameplayStatics::CreateSaveGameObject(UDAPlayerSave::StaticClass()));
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

void UDAGameInstance::DeletePlayerSave(FString PlayerName)
{
	if (!Settings) {
		InitSettings();
	}

	if (Settings) {
		Settings->CharacterNames.Remove(PlayerName);
		UGameplayStatics::SaveGameToSlot(Settings, "Master", 0);
	}

	UGameplayStatics::DeleteGameInSlot(PlayerName, 0);
}