// Fill out your copyright notice in the Description page of Project Settings.

#include "DALevelWidget.h"
#include "DAIncrementButton.h"
#include "DAGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "DAPlayer.h"

void UDALevelWidget::SetupWithAttributesAndSouls(FDACharacterAttributes Attributes, int Souls)
{
	CurrentAttributes = Attributes;
	HealthStat = Attributes.HealthStat;
	StaminaStat = Attributes.StaminaStat;
	DamageStat = Attributes.DamageStat;
	PracticalStat = Attributes.PracticalStat;
	ScientificStat = Attributes.ScientificStat;
	SpiritualStat = Attributes.SpiritualStat;
	CurrentSouls = Souls;
	CurrentCost = 0;
	NextCost = FDACharacterAttributes::GetCostForLevel(GetCurrentLevel() + 1);
}

void UDALevelWidget::CommitLevelUp()
{
	CurrentAttributes.HealthStat = HealthStat;
	CurrentAttributes.StaminaStat = StaminaStat;
	CurrentAttributes.DamageStat = DamageStat;
	CurrentAttributes.PracticalStat = PracticalStat;
	CurrentAttributes.ScientificStat = ScientificStat;
	CurrentAttributes.SpiritualStat = SpiritualStat;
	CurrentSouls -= CurrentCost;

	ADAPlayer* Player = Cast<ADAPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->UpdateAttributes(CurrentAttributes);
	Player->ConsumeSouls(CurrentCost);

	CurrentCost = 0;
}

void UDALevelWidget::IncrementStat(EDACharacterStat Stat)
{
	int cost = FDACharacterAttributes::GetCostForLevel(GetCurrentLevel() + 1);

	if (cost + CurrentCost > CurrentSouls) {
		return;
	}

	CurrentCost += cost;
	switch (Stat)
	{
	case EDACharacterStat::DACharacterStat_Health:
		HealthStat++;
		break;
	case EDACharacterStat::DACharacterStat_Stamina:
		StaminaStat++;
		break;
	case EDACharacterStat::DACharacterStat_Damage:
		DamageStat++;
		break;
	case EDACharacterStat::DACharacterStat_Scientific:
		ScientificStat++;
		break;
	case EDACharacterStat::DACharacterStat_Practical:
		PracticalStat++;
		break;
	case EDACharacterStat::DACharacterStat_Spiritual:
		SpiritualStat++;
		break;
	default:
		break;
	}
	NextCost = FDACharacterAttributes::GetCostForLevel(GetCurrentLevel() + 1);
}

void UDALevelWidget::DecrementStat(EDACharacterStat Stat)
{
	int cost = FDACharacterAttributes::GetCostForLevel(GetCurrentLevel());

	switch (Stat)
	{
	case EDACharacterStat::DACharacterStat_Health:
		if (HealthStat > CurrentAttributes.HealthStat) {
			HealthStat--;
			CurrentCost -= cost;
		}
		break;
	case EDACharacterStat::DACharacterStat_Stamina:
		if (StaminaStat > CurrentAttributes.StaminaStat) {
			StaminaStat--;
			CurrentCost -= cost;
		}
		break;
	case EDACharacterStat::DACharacterStat_Damage:
		if (DamageStat > CurrentAttributes.DamageStat) {
			DamageStat--;
			CurrentCost -= cost;
		}
		break;
	case EDACharacterStat::DACharacterStat_Scientific:
		if (ScientificStat > CurrentAttributes.ScientificStat) {
			ScientificStat--;
			CurrentCost -= cost;
		}
		break;
	case EDACharacterStat::DACharacterStat_Practical:
		if (PracticalStat > CurrentAttributes.PracticalStat) {
			PracticalStat--;
			CurrentCost -= cost;
		}
		break;
	case EDACharacterStat::DACharacterStat_Spiritual:
		if (SpiritualStat > CurrentAttributes.SpiritualStat) {
			SpiritualStat--;
			CurrentCost -= cost;
		}
		break;
	default:
		break;
	}
	NextCost = FDACharacterAttributes::GetCostForLevel(GetCurrentLevel() + 1);
}

void UDALevelWidget::NavigateRight()
{
	UDAIncrementButton* Button = Cast<UDAIncrementButton>(CurrentHighlight);
	if (Button) {
		Button->IncrementAction.Broadcast(true);
	}
}

void UDALevelWidget::NavigateLeft()
{
	UDAIncrementButton* Button = Cast<UDAIncrementButton>(CurrentHighlight);
	if (Button) {
		Button->IncrementAction.Broadcast(false);
	}
}

