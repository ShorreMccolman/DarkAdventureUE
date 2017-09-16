// Fill out your copyright notice in the Description page of Project Settings.

#include "DATextBox.h"
#include "Components/EditableTextBox.h"
#include "Components/Border.h"
#include "Text.h"

void UDATextBox::Highlight_Implementation()
{
	if (Border) {
		Border->SetBrushColor(FLinearColor::Blue);
	}
}

void UDATextBox::UnHighlight_Implementation()
{
	if (Border) {
		Border->SetBrushColor(FLinearColor::White);
	}
}

void UDATextBox::OnSelect_Implementation()
{
	if (TextBox) {
		TextBox->SetHintText(FText::FromName("Enter Name..."));
		TextBox->SetKeyboardFocus();
		Border->SetBrushColor(FLinearColor::Red);
	}
}
