// Fill out your copyright notice in the Description page of Project Settings.

#include "DACharacterSelectMenu.h"
#include "WidgetNavigation.h"
#include "DACharacterProfileButton.h"
#include "Kismet/GameplayStatics.h"
#include "DAMasterSettings.h"

UDACharacterSelectMenu::UDACharacterSelectMenu()
{
	CharacterNames = { "John","Jack","Steve","Tom" };
	CurrentIndex = 0;
}

void UDACharacterSelectMenu::LoadCharacterNames()
{
	UDAMasterSettings* Settings = Cast<UDAMasterSettings>(UGameplayStatics::CreateSaveGameObject(UDAMasterSettings::StaticClass()));
	Settings = Cast<UDAMasterSettings>(UGameplayStatics::LoadGameFromSlot("Master", 0));
	if (!Settings) {
		Settings = Cast<UDAMasterSettings>(UGameplayStatics::CreateSaveGameObject(UDAMasterSettings::StaticClass()));
		if (Settings) {
			Settings->CharacterNames.Add("DA_Default");
		}
	}
	CharacterNames = Settings->CharacterNames;
}


void UDACharacterSelectMenu::NavigateUp()
{
	if (CurrentIndex > 0) {
		CurrentIndex--;
		UWidget* Widget = CharacterButtons[CurrentIndex];
		if (Widget) {
			SetHighlight(Widget);
		}
	}
}

void UDACharacterSelectMenu::NavigateRight()
{

}

void UDACharacterSelectMenu::NavigateDown()
{
	if (CurrentIndex < CharacterNames.Num() - 1) {
		CurrentIndex++;
		UWidget* Widget = CharacterButtons[CurrentIndex];
		if (Widget) {
			SetHighlight(Widget);
		}
	}
}

void UDACharacterSelectMenu::NavigateLeft()
{

}
