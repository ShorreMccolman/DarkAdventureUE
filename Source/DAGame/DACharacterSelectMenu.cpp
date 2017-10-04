// Fill out your copyright notice in the Description page of Project Settings.

#include "DACharacterSelectMenu.h"
#include "WidgetNavigation.h"
#include "DACharacterProfileButton.h"
#include "Kismet/GameplayStatics.h"
#include "DAMasterSettings.h"
#include "DAGameInstance.h"

void UDACharacterSelectMenu::LoadCharacterProfiles()
{
	UGameInstance* Inst = UGameplayStatics::GetGameInstance(GetWorld());
	if (Inst) {
		UDAGameInstance* GI = Cast<UDAGameInstance>(Inst);
		if (GI) {
			const UDAMasterSettings* Settings = GI->GetSettings();
			if (Settings) {
				CharacterProfiles.Empty();
				for (int i = 0; i < Settings->CharacterIDs.Num(); i++) {
					UDAPlayerProfile* Prof = GI->LoadPlayerProfile(Settings->CharacterIDs[i]);
					if (Prof) {
						CharacterProfiles.Add(Prof);
					}
				}
			}
		}
	}
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
	if (CurrentIndex < CharacterProfiles.Num() - 1) {
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
