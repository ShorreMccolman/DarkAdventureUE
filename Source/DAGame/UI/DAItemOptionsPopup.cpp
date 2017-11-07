// Fill out your copyright notice in the Description page of Project Settings.

#include "DAItemOptionsPopup.h"
#include "DAItemButton.h"



void UDAItemOptionsPopup::DoUseAction()
{
	if (UseAction.IsBound()) {
		UseAction.Broadcast(Button);
	}
}

void UDAItemOptionsPopup::DoDiscardAction()
{
	if (DiscardAction.IsBound()) {
		DiscardAction.Broadcast(Button);
	}
}
