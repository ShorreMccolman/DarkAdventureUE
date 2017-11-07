// Fill out your copyright notice in the Description page of Project Settings.

#include "DACharacterAttributePanel.h"


void UDACharacterAttributePanel::InitWithWorldviewAndMotive(EDAWorldview WorldView, EDAMotive Motive)
{
	Attributes = FDACharacterAttributes(WorldView, Motive);

	
}

FString UDACharacterAttributePanel::GetClassText(EDAWorldview WorldView, EDAMotive Motive)
{
	return FDACharacterAttributes::GetClassTextFromWorldviewAndMotive(WorldView, Motive);
}
