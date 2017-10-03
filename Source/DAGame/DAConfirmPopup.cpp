// Fill out your copyright notice in the Description page of Project Settings.

#include "DAConfirmPopup.h"
#include "DAGameMode.h"

void UDAConfirmPopup::DoConfirmation()
{
	bool isBound = ConfirmAction.ExecuteIfBound();
	if(isBound)
		ConfirmAction.Unbind();
	ADAGameMode* Mode = Cast<ADAGameMode>(GetWorld()->GetAuthGameMode());
	if (Mode) {
		Mode->ClosePopup();
	}
}


