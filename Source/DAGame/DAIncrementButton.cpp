// Fill out your copyright notice in the Description page of Project Settings.

#include "DAIncrementButton.h"
#include "DAButton.h"


void UDAIncrementButton::Highlight_Implementation()
{
	Button->SetBackgroundColor(FLinearColor(1.0f, 0.35f, 0.2f));
}

void UDAIncrementButton::UnHighlight_Implementation()
{
	Button->SetBackgroundColor(FLinearColor::White);
}

void UDAIncrementButton::OnSelect_Implementation()
{
	//UDAGameInstance* Instance = Cast<UDAGameInstance>(GetWorld()->GetGameInstance());
	//if (Instance) {
	//	Instance->TryLoadGame(CharacterProfile->ID);
	//}
}

