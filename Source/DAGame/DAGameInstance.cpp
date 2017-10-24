// Fill out your copyright notice in the Description page of Project Settings.

#include "DAGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "DAPlayerSave.h"
#include "DAMasterSettings.h"
#include "DAPlayerProfile.h"
#include "DAGameMode.h"

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
	OpenLevel("Main");
}

void UDAGameInstance::OpenLevel(FName LevelName)
{
	ADAGameMode* Mode = Cast<ADAGameMode>(GetWorld()->GetAuthGameMode());
	if (Mode) {
		Mode->ShowLoadingScreen();
		UGameplayStatics::OpenLevel(this, LevelName);
	}
}

void UDAGameInstance::TryLoadGame(FString PlayerID)
{
	if (!Settings) {
		InitSettings();
	}

	if (Settings) {
		Settings->SetCurrentCharacter(PlayerID);
		UGameplayStatics::SaveGameToSlot(Settings, "Master", 0);
	}
	OpenLevel("Main");
}

void UDAGameInstance::TryCreateNewGame(FString PlayerName, FDACharacterAttributes Attributes)
{
	CreatePlayerSave(PlayerName, Attributes);
	OpenLevel("Main");
}

void UDAGameInstance::UpdateCurrentPlayerLevel(int Level)
{
	Profile->Level = Level;
	FString ProfID = FString(*Profile->ID).Append("-Prof");
	UGameplayStatics::SaveGameToSlot(Profile, ProfID, 0);
}

void UDAGameInstance::CreatePlayerSave(FString PlayerName, FDACharacterAttributes Attributes)
{
	FGuid guid = FGuid::NewGuid();
	FString PlayerID = guid.ToString();

	PlayerSave = Cast<UDAPlayerSave>(UGameplayStatics::CreateSaveGameObject(UDAPlayerSave::StaticClass()));
	PlayerSave->ID = PlayerID;
	PlayerSave->PlayerName = PlayerName;
	PlayerSave->Attributes = Attributes;

	FDACharacterInventory Inventory = FDACharacterInventory();
	ADAGameMode* Mode = Cast<ADAGameMode>(GetWorld()->GetAuthGameMode());
	UDAItemManager* IM = Mode->GetItemManager();
	if (IM) {
		Inventory.SetupAsNewPlayerInventory(Attributes, IM);
	}
	PlayerSave->Inventory = Inventory;

	PlayerSave->bIsNewPlayer = true;
	UGameplayStatics::SaveGameToSlot(PlayerSave, PlayerID, 0);

	Profile = Cast<UDAPlayerProfile>(UGameplayStatics::CreateSaveGameObject(UDAPlayerProfile::StaticClass()));
	Profile->ID = PlayerID;
	Profile->PlayerName = PlayerName;
	Profile->Level = Attributes.GetLevel();
	Profile->Worldview = Attributes.WorldView;
	Profile->Motive = Attributes.Motive;
	FString ProfID = FString(PlayerID);
	ProfID.Append("-Prof");
	UGameplayStatics::SaveGameToSlot(Profile, ProfID, 0);

	if (!Settings) {
		InitSettings();
	}

	if (Settings) {
		Settings->CharacterIDs.AddUnique(PlayerID);
		Settings->SetCurrentCharacter(PlayerID);
		Settings->bHasCharacter = true;
		UGameplayStatics::SaveGameToSlot(Settings, "Master", 0);
	}
}

UDAPlayerSave* UDAGameInstance::LoadCurrentPlayerSave()
{
	if (!Settings) {
		InitSettings();
	}

	if (Settings) {
		PlayerSave = Cast<UDAPlayerSave>(UGameplayStatics::CreateSaveGameObject(UDAPlayerSave::StaticClass()));
		PlayerSave = Cast<UDAPlayerSave>(UGameplayStatics::LoadGameFromSlot(Settings->CurrentCharacterID, 0));

		Profile = LoadPlayerProfile(Settings->CurrentCharacterID);
		if (!Profile) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to load character profile"))
		}

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

UDAPlayerProfile* UDAGameInstance::LoadPlayerProfile(FString ID)
{
	FString ProfID = FString(ID);
	ProfID.Append("-Prof");

	UDAPlayerProfile* Prof = Cast<UDAPlayerProfile>(UGameplayStatics::CreateSaveGameObject(UDAPlayerProfile::StaticClass()));
	Prof = Cast<UDAPlayerProfile>(UGameplayStatics::LoadGameFromSlot(ProfID, 0));
	return Prof;
}

void UDAGameInstance::DeletePlayerSave(FString ID)
{
	if (!Settings) {
		InitSettings();
	}

	if (Settings) {
		Settings->CharacterIDs.Remove(ID);

		if (Settings->CurrentCharacterID.Equals(ID)) {
			Settings->ClearCurrentCharacter();
		}


		UGameplayStatics::SaveGameToSlot(Settings, "Master", 0);
	}
	UGameplayStatics::DeleteGameInSlot(ID, 0);
	FString ProfID = FString(ID);
	UGameplayStatics::DeleteGameInSlot(ProfID.Append("-Prof"), 0);
}