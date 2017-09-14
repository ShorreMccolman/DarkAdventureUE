// Fill out your copyright notice in the Description page of Project Settings.

#include "DACharacterProfileButton.h"
#include "Components/Button.h"


void UDACharacterProfileButton::Highlight_Implementation()
{
	Button->SetBackgroundColor(FLinearColor::Blue);
}

void UDACharacterProfileButton::UnHighlight_Implementation()
{
	Button->SetBackgroundColor(FLinearColor::White);
}

void UDACharacterProfileButton::OnSelect_Implementation()
{
	//OnClicked.Broadcast();
}

