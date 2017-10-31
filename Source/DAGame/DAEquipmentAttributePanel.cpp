// Fill out your copyright notice in the Description page of Project Settings.

#include "DAEquipmentAttributePanel.h"
#include "DAGeneratedAttributes.h"
#include "DACharacter.h"


void UDAEquipmentAttributePanel::InitWithCharacter(ADACharacter* PlayerCharacter)
{
	Attributes = PlayerCharacter->GetGeneratedAttributes();
	
	UpdateDisplay();
}

