// Fill out your copyright notice in the Description page of Project Settings.

#include "DAButton.h"

void UDAButton::SetDisabled(bool IsDisabled)
{
	bIsDisabled = IsDisabled;
	SetBackgroundColor(bIsDisabled ? FLinearColor(0.15f, 0.15f, 0.15f) : FLinearColor::White);
}

void UDAButton::Highlight_Implementation()
{
	if (bIsDisabled) 
	{
		SetBackgroundColor(FLinearColor(0.15f, 0.15f, 0.8f));
	} 
	else 
	{
		SetBackgroundColor(FLinearColor(1.0f, 0.35f, 0.2f));
	}
}

void UDAButton::UnHighlight_Implementation()
{
	if (bIsDisabled)
	{
		SetBackgroundColor(FLinearColor(0.15f, 0.15f, 0.15f));
	}
	else
	{
		SetBackgroundColor(FLinearColor::White);
	}
}

void UDAButton::OnSelect_Implementation()
{
	if (!bIsDisabled) 
	{
		OnClicked.Broadcast();
	}
}