// Fill out your copyright notice in the Description page of Project Settings.

#include "DAEquipmentAttributePanel.h"
#include "DACharacter.h"


void UDAEquipmentAttributePanel::InitWithCharacter(ADACharacter* PlayerCharacter)
{
	Character = PlayerCharacter;
	Attributes = FDAGeneratedAttributes(*PlayerCharacter);
	
	UpdateDisplay();
}

