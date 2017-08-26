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

	FDACharacterAttributes()
	{
		MaxHealth = 100.f;
		CurHealth = MaxHealth;

		MaxStamina = 100.f;
		CurStamina = MaxStamina;
	}

	FDACharacterAttributes(float Health, float Stamina)
	{
		MaxHealth = Health;
		CurHealth = MaxHealth;

		MaxStamina = Stamina;
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