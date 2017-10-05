// Fill out your copyright notice in the Description page of Project Settings.

#include "DAMasterSettings.h"

UDAMasterSettings::UDAMasterSettings()
{
	bHasCharacter = false;
}

void UDAMasterSettings::SetCurrentCharacter(FString ID)
{
	CurrentCharacterID = ID;
	bHasCurrentCharacter = true;
}

void UDAMasterSettings::ClearCurrentCharacter()
{
	CurrentCharacterID = "";
	bHasCurrentCharacter = false;
}