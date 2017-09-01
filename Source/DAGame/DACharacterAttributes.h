#pragma once

#include "CoreMinimal.h"
#include "DACharacterAttributes.generated.h"

USTRUCT()
struct FDACharacterAttributes 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Vitality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Endurance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Strength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Dexterity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Intellect;

	FDACharacterAttributes()
	{
		Vitality = 10;
		Endurance = 10;
		Strength = 10;
		Dexterity = 10;
		Intellect = 10;

		MaxHealth = 10.f * Vitality;
		CurHealth = MaxHealth;

		MaxStamina = 10.f * Endurance;
		CurStamina = MaxStamina;
	}

	void Reset()
	{
		CurHealth = MaxHealth;
		CurStamina = MaxStamina;
	}

	bool HasSufficientStamina(float amount)
	{
		return CurStamina >= amount;
	}

	void ConsumeStamina(float amount)
	{
		CurStamina = FMath::Clamp<float>(CurStamina - amount, 0.f, MaxStamina);
	}

	void RegainStamina(float amount)
	{
		CurStamina = FMath::Clamp<float>(CurStamina + amount, 0.f, MaxStamina);
	}
};