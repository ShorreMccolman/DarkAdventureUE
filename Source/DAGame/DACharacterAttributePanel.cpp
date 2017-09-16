// Fill out your copyright notice in the Description page of Project Settings.

#include "DACharacterAttributePanel.h"


void UDACharacterAttributePanel::InitWithWorldviewAndMotive(EDAWorldview WorldView, EDAMotive Motive)
{
	HealthStatValue = 10;
	StaminaStatValue = 10;
	DamageStatValue = 10;
	PracticalStatValue = 10;
	ScientificStatValue = 10;
	SpiritualStatValue = 10;

	switch (WorldView)
	{
	case EDAWorldview::DAWorldView_None:
		break;
	case EDAWorldview::DAWorldView_Spritual:
		SpiritualStatValue += 3;
		ScientificStatValue -= 2;
		PracticalStatValue -= 1;
		break;
	case EDAWorldview::DAWorldView_Practical:
		HealthStatValue += 1;
		StaminaStatValue += 1;
		DamageStatValue += 1;
		PracticalStatValue += 3;
		ScientificStatValue -= 3;
		SpiritualStatValue -= 3;
		break;
	case EDAWorldview::DAWorldView_Scientific:
		HealthStatValue -= 1;
		SpiritualStatValue -= 3;
		ScientificStatValue += 4;
		break;
	default:
		break;
	}

	switch (Motive)
	{
	case EDAMotive::DAMotive_None:
		break;
	case EDAMotive::DAMotive_Duty:
		HealthStatValue += 2;
		StaminaStatValue += 2;
		DamageStatValue -= 0;
		PracticalStatValue -= 1;
		ScientificStatValue -= 3;
		SpiritualStatValue += 0;
		break;
	case EDAMotive::DAMotive_Glory:
		HealthStatValue -= 1;
		StaminaStatValue += 1;
		DamageStatValue += 3;
		PracticalStatValue -= 2;
		ScientificStatValue -= 2;
		SpiritualStatValue += 1;
		break;
	case EDAMotive::DAMotive_Profit:
		HealthStatValue += 2;
		StaminaStatValue -= 2;
		DamageStatValue -= 1;
		PracticalStatValue += 3;
		ScientificStatValue += 1;
		SpiritualStatValue -= 3;
		break;
	case EDAMotive::DAMotive_Power:
		HealthStatValue += 2;
		StaminaStatValue -= 2;
		DamageStatValue += 2;
		PracticalStatValue += 1;
		ScientificStatValue += 1;
		SpiritualStatValue += 1;
		break;
	default:
		break;
	}
}

FString UDACharacterAttributePanel::GetClassTextFromWorldviewAndMotive(EDAWorldview WorldView, EDAMotive Motive)
{
	switch (WorldView)
	{
	case EDAWorldview::DAWorldView_None:
		return "Choose a worldview";
	case EDAWorldview::DAWorldView_Spritual:

		switch (Motive)
		{
		case EDAMotive::DAMotive_None:
			return "Choose a motive";
		case EDAMotive::DAMotive_Duty:
			return "Knight";
		case EDAMotive::DAMotive_Glory:
			return "Cleric";
		case EDAMotive::DAMotive_Power:
			return "Zealot";
		default:
			break;
		}

		break;
	case EDAWorldview::DAWorldView_Practical:

		switch (Motive)
		{
		case EDAMotive::DAMotive_None:
			return "Choose a motive";
		case EDAMotive::DAMotive_Duty:
			return "Soldier";
		case EDAMotive::DAMotive_Profit:
			return "Mercenary";
		case EDAMotive::DAMotive_Power:
			return "Survivor";
		default:
			break;
		}

		break;
	case EDAWorldview::DAWorldView_Scientific:

		switch (Motive)
		{
		case EDAMotive::DAMotive_None:
			return "Choose a motive";
		case EDAMotive::DAMotive_Glory:
			return "Illusionist";
		case EDAMotive::DAMotive_Profit:
			return "Inventor";
		case EDAMotive::DAMotive_Power:
			return "Controller";
		default:
			break;
		}

		break;
	default:
		break;
	}

	return "???";
}