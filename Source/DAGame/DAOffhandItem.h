// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAItem.h"
#include "DAOffhandItem.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API UDAOffhandItem : public UDAItem
{
	GENERATED_BODY()
	
public:
	UDAOffhandItem();

	virtual void ModifyGeneratedAttributes(class UDAGeneratedAttributes& Attributes) const override;
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE FString GetOffhandTypeDescription() const {
		switch (OffhandType)
		{
		case EDAOffhandType::DAOffhandType_Shield:
			return "Shield";
		case EDAOffhandType::DAOffhandType_Dual:
			return "Dual Wield";
		default:
			return "";
		}
	}

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetOffensivePower() const { return OffensivePower; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetDefensivePower() const { return DefensivePower; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetDamageRequirement() const { return DamageRequirement; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetScienceRequirement() const { return ScienceRequirement; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetPracticalRequirement() const { return PracticalRequirement; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetSpiritRequirement() const { return SpiritRequirement; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDAOffhandType OffhandType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int OffensivePower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DefensivePower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DamageRequirement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ScienceRequirement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PracticalRequirement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SpiritRequirement;

};
