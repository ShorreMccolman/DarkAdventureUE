// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DACharacterAttributes.h"
#include "DACharacterAttributePanel.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API UDACharacterAttributePanel : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDACharacterAttributes Attributes;

	UFUNCTION(BlueprintCallable)
	void InitWithWorldviewAndMotive(EDAWorldview WorldView, EDAMotive Motive);

	UFUNCTION(BlueprintCallable)
	FString GetClassText(EDAWorldview WorldView, EDAMotive Motive);

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetCharacterLevel() const { return Attributes.HealthStat + Attributes.StaminaStat + Attributes.DamageStat + Attributes.PracticalStat + Attributes.ScientificStat + Attributes.SpiritualStat - 59; }
	
};
