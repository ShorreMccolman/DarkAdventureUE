// Fill out your copyright notice in the Description page of Project Settings.

#include "DAQuantityPopup.h"
#include "DAGameMode.h"
#include "DAIncrementButton.h"

void UDAQuantityPopup::SetMaxQuantity(int Quantity)
{
	CurrentQuantity = 1;
	MaxQuantity = Quantity;
	UpdateDisplay();
}

void UDAQuantityPopup::Accept()
{
	ADAGameMode* Mode = Cast<ADAGameMode>(GetWorld()->GetAuthGameMode());
	if (Mode) {
		Mode->ClosePopup();
	}
	if (ConfirmAction.IsBound()) {
		ConfirmAction.Broadcast(CurrentQuantity);
	}
}

void UDAQuantityPopup::IncreaseQuantity()
{
	CurrentQuantity = FMath::Min<int>(CurrentQuantity + 1, MaxQuantity);
	UpdateDisplay();
}

void UDAQuantityPopup::DecreaseQuantity()
{
	CurrentQuantity = FMath::Max<int>(CurrentQuantity - 1, 1);
	UpdateDisplay();
}

void UDAQuantityPopup::NavigateRight()
{
	if (Button) {
		Button->IncrementAction.Broadcast(true);
	}
}

void UDAQuantityPopup::NavigateLeft()
{
	if (Button) {
		Button->IncrementAction.Broadcast(false);
	}
}