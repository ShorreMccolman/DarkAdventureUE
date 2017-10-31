// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAWidget.h"
#include "DACharacterAttributes.h"
#include "DALevelWidget.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API UDALevelWidget : public UDAWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void CommitLevelUp();

	UFUNCTION(BlueprintCallable)
	void SetupWithAttributesAndSouls(FDACharacterAttributes Attributes, int Souls);

	UFUNCTION(BlueprintCallable)
	void IncrementStat(EDACharacterStat Stat);

	UFUNCTION(BlueprintCallable)
	void DecrementStat(EDACharacterStat Stat);

	UFUNCTION(BlueprintCallable)
	virtual void NavigateRight() override;

	UFUNCTION(BlueprintCallable)
	virtual void NavigateLeft() override;

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetCurrentLevel() const { return HealthStat + StaminaStat + DamageStat + PracticalStat + ScientificStat + SpiritualStat - 59; }
	
protected:
	UPROPERTY(BlueprintReadWrite)
	FDACharacterAttributes CurrentAttributes;

	UPROPERTY(BlueprintReadWrite)
	int CurrentSouls;


	UPROPERTY(BlueprintReadWrite)
	int HealthStat;
	UPROPERTY(BlueprintReadWrite)
	int StaminaStat;
	UPROPERTY(BlueprintReadWrite)
	int DamageStat;
	UPROPERTY(BlueprintReadWrite)
	int PracticalStat;
	UPROPERTY(BlueprintReadWrite)
	int ScientificStat;
	UPROPERTY(BlueprintReadWrite)
	int SpiritualStat;

	UPROPERTY(BlueprintReadWrite)
	int CurrentCost;
	UPROPERTY(BlueprintReadWrite)
	int NextCost;
};
