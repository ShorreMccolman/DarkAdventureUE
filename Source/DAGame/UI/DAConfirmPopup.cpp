// Fill out your copyright notice in the Description page of Project Settings.

#include "DAConfirmPopup.h"
#include "DAGameMode.h"

void UDAConfirmPopup::DoConfirmation()
{
	if (ConfirmAction.IsBound()) {
		ConfirmAction.Broadcast();
	}
	ADAGameMode* Mode = Cast<ADAGameMode>(GetWorld()->GetAuthGameMode());
	if (Mode) {
		Mode->ClosePopup();
	}
}


