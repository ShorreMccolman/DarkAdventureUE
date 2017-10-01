// Fill out your copyright notice in the Description page of Project Settings.

#include "DACharacterProfileButton.h"
#include "Components/Button.h"
#include "DAGameInstance.h"


void UDACharacterProfileButton::Highlight_Implementation()
{
	Button->SetBackgroundColor(FLinearColor(1.0f, 0.35f, 0.2f));
}

void UDACharacterProfileButton::UnHighlight_Implementation()
{
	Button->SetBackgroundColor(FLinearColor::White);
}

void UDACharacterProfileButton::OnSelect_Implementation()
{
	UDAGameInstance* Instance = Cast<UDAGameInstance>(GetWorld()->GetGameInstance());
	if (Instance) {
		Instance->TryLoadGame(CharacterName);
	}
}

