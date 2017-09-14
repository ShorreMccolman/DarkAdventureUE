// Fill out your copyright notice in the Description page of Project Settings.

#include "DAButton.h"

void UDAButton::Highlight_Implementation()
{
	SetBackgroundColor(FLinearColor::Blue);
}

void UDAButton::UnHighlight_Implementation()
{
	SetBackgroundColor(FLinearColor::White);
}

void UDAButton::OnSelect_Implementation()
{
	OnClicked.Broadcast();
}