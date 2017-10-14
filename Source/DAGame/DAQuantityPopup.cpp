// Fill out your copyright notice in the Description page of Project Settings.

#include "DAQuantityPopup.h"
#include "DAGameMode.h"

void UDAQuantityPopup::SetMaxQuantity(int Quantity)
{
	CurrentQuantity = 1;
	MaxQuantity = Quantity;
	UpdateDisplay();
}

void UDAQuantityPopup::Accept()
{
	if (ConfirmAction.IsBound()) {
		ConfirmAction.Broadcast(CurrentQuantity);
	}
	ADAGameMode* Mode = Cast<ADAGameMode>(GetWorld()->GetAuthGameMode());
	if (Mode) {
		Mode->ClosePopup();
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
	IncreaseQuantity();
}

void UDAQuantityPopup::NavigateLeft()
{
	DecreaseQuantity();
}