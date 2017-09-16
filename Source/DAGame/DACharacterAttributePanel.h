// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DACharacterAttributePanel.generated.h"

UENUM(BlueprintType)
enum class EDAWorldview : uint8
{
	DAWorldView_None UMETA(DisplayName = "None"),
	DAWorldView_Spritual UMETA(DisplayName = "Spiritual"),
	DAWorldView_Practical UMETA(DisplayName = "Practical"),
	DAWorldView_Scientific UMETA(DisplayName = "Scientific")
};

UENUM(BlueprintType)
enum class EDAMotive : uint8
{
	DAMotive_None UMETA(DisplayName = "None"),
	DAMotive_Duty UMETA(DisplayName = "Duty"),
	DAMotive_Glory UMETA(DisplayName = "Glory"),
	DAMotive_Profit UMETA(DisplayName = "Profit"),
	DAMotive_Power UMETA(DisplayName = "Power")
};

/**
 * 
 */
UCLASS()
class DAGAME_API UDACharacterAttributePanel : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HealthStatValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StaminaStatValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DamageStatValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PracticalStatValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ScientificStatValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SpiritualStatValue;

	UFUNCTION(BlueprintCallable)
	void InitWithWorldviewAndMotive(EDAWorldview WorldView, EDAMotive Motive);

	UFUNCTION(BlueprintPure)
	FString GetClassTextFromWorldviewAndMotive(EDAWorldview WorldView, EDAMotive Motive);

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetCharacterLevel() const { return HealthStatValue + StaminaStatValue + DamageStatValue + PracticalStatValue + ScientificStatValue + SpiritualStatValue - 59; }
	
};
