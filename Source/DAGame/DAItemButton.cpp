// Fill out your copyright notice in the Description page of Project Settings.

#include "DAItemButton.h"
#include "DAItem.h"
#include "Components/Image.h"
#include "Components/Button.h"



void UDAItemButton::Highlight_Implementation()
{
	Button->SetBackgroundColor(FLinearColor(1.0f, 0.35f, 0.2f));
}

void UDAItemButton::UnHighlight_Implementation()
{
	Button->SetBackgroundColor(FLinearColor::White);
}

void UDAItemButton::OnSelect_Implementation()
{
//	UDAGameInstance* Instance = Cast<UDAGameInstance>(GetWorld()->GetGameInstance());
	//if (Instance) {
	//	Instance->TryLoadGame(CharacterProfile->ID);
	//}
}

void UDAItemButton::SetItem(UDAItem* Item)
{
	this->Item = Item;

	IconImage->SetBrushFromTexture(Item->Icon);
}
