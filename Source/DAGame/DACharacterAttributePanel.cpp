// Fill out your copyright notice in the Description page of Project Settings.

#include "DACharacterAttributePanel.h"


void UDACharacterAttributePanel::InitWithWorldviewAndMotive(EDAWorldview WorldView, EDAMotive Motive)
{
	Attributes = FDACharacterAttributes();

	switch (WorldView)
	{
	case EDAWorldview::DAWorldView_None:
		break;
	case EDAWorldview::DAWorldView_Spritual:
		Attributes.SpiritualStat += 3;
		Attributes.ScientificStat -= 2;
		Attributes.PracticalStat -= 1;
		break;
	case EDAWorldview::DAWorldView_Practical:
		Attributes.HealthStat += 1;
		Attributes.StaminaStat += 1;
		Attributes.DamageStat += 1;
		Attributes.PracticalStat += 3;
		Attributes.ScientificStat -= 3;
		Attributes.SpiritualStat -= 3;
		break;
	case EDAWorldview::DAWorldView_Scientific:
		Attributes.HealthStat -= 1;
		Attributes.SpiritualStat -= 3;
		Attributes.ScientificStat += 4;
		break;
	default:
		break;
	}

	switch (Motive)
	{
	case EDAMotive::DAMotive_None:
		break;
	case EDAMotive::DAMotive_Duty:
		Attributes.HealthStat += 2;
		Attributes.StaminaStat += 2;
		Attributes.DamageStat -= 0;
		Attributes.PracticalStat -= 1;
		Attributes.ScientificStat -= 3;
		Attributes.SpiritualStat += 0;
		break;
	case EDAMotive::DAMotive_Glory:
		Attributes.HealthStat -= 1;
		Attributes.StaminaStat += 1;
		Attributes.DamageStat += 3;
		Attributes.PracticalStat -= 2;
		Attributes.ScientificStat -= 2;
		Attributes.SpiritualStat += 1;
		break;
	case EDAMotive::DAMotive_Profit:
		Attributes.HealthStat += 2;
		Attributes.StaminaStat -= 2;
		Attributes.DamageStat -= 1;
		Attributes.PracticalStat += 3;
		Attributes.ScientificStat += 1;
		Attributes.SpiritualStat -= 3;
		break;
	case EDAMotive::DAMotive_Power:
		Attributes.HealthStat += 2;
		Attributes.StaminaStat -= 2;
		Attributes.DamageStat += 2;
		Attributes.PracticalStat += 1;
		Attributes.ScientificStat += 1;
		Attributes.SpiritualStat += 1;
		break;
	default:
		break;
	}

	Attributes.Reset();
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