// Fill out your copyright notice in the Description page of Project Settings.

#include "DAHUDWidget.h"


void UDAHUDWidget::UpdateCharacterAndDisplay(class ADACharacter* PlayerCharacter)
{
	Character = PlayerCharacter;
	DoDisplayUpdate();
}

