#pragma once

#include "CoreMinimal.h"
#include "DACharacterAttributes.generated.h"

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

UENUM(BlueprintType)
enum class EDACharacterStat : uint8
{
	DACharacterStat_Health UMETA(DisplayName = "Health"),
	DACharacterStat_Stamina UMETA(DisplayName = "Stamina"),
	DACharacterStat_Damage UMETA(DisplayName = "Damage"),
	DACharacterStat_Scientific UMETA(DisplayName = "Scientific"),
	DACharacterStat_Practical UMETA(DisplayName = "Practical"),
	DACharacterStat_Spiritual UMETA(DisplayName = "Spiritual")
};


USTRUCT(BlueprintType)
struct FDACharacterAttributes 
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	float MaxHealth;
	UPROPERTY(BlueprintReadWrite)
	float CurHealth;

	UPROPERTY(BlueprintReadWrite)
	float MaxStamina;
	UPROPERTY(BlueprintReadWrite)
	float CurStamina;

	UPROPERTY(BlueprintReadWrite)
	int CurrentSouls;
	UPROPERTY(BlueprintReadWrite)
	bool bHasLostSouls;
	UPROPERTY(BlueprintReadWrite)
	FVector LostSoulsLocation;
	UPROPERTY(BlueprintReadWrite)
	int LostSouls;

	UPROPERTY(BlueprintReadWrite)
	int MaxHeals;

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
	EDAWorldview WorldView;
	UPROPERTY(BlueprintReadWrite)
	EDAMotive Motive;

	FDACharacterAttributes()
	{
		HealthStat = 10;
		StaminaStat = 10;
		DamageStat = 10;
		PracticalStat = 10;
		ScientificStat = 10;
		SpiritualStat = 10;

		MaxHeals = 5;

		MaxHealth = 10.f * HealthStat;
		CurHealth = MaxHealth;

		MaxStamina = 10.f * StaminaStat;
		CurStamina = MaxStamina;

		CurrentSouls = 0;
		bHasLostSouls = false;
		LostSoulsLocation = FVector::ZeroVector;
		LostSouls = 0;

		WorldView = EDAWorldview::DAWorldView_None;
		Motive = EDAMotive::DAMotive_None;
	}

	FDACharacterAttributes(EDAWorldview WorldView, EDAMotive Motive) : WorldView(WorldView), Motive(Motive)
	{
		HealthStat = 10;
		StaminaStat = 10;
		DamageStat = 10;
		PracticalStat = 10;
		ScientificStat = 10;
		SpiritualStat = 10;

		MaxHeals = 5;

		MaxHealth = 10.f * HealthStat;
		CurHealth = MaxHealth;

		MaxStamina = 10.f * StaminaStat;
		CurStamina = MaxStamina;

		CurrentSouls = 1000;
		bHasLostSouls = false;
		LostSoulsLocation = FVector::ZeroVector;
		LostSouls = 0;

		switch (WorldView)
		{
		case EDAWorldview::DAWorldView_None:
			break;
		case EDAWorldview::DAWorldView_Spritual:
			SpiritualStat += 3;
			ScientificStat -= 2;
			PracticalStat -= 1;
			break;
		case EDAWorldview::DAWorldView_Practical:
			HealthStat += 1;
			StaminaStat += 1;
			DamageStat += 1;
			PracticalStat += 3;
			ScientificStat -= 3;
			SpiritualStat -= 3;
			break;
		case EDAWorldview::DAWorldView_Scientific:
			HealthStat -= 1;
			SpiritualStat -= 3;
			ScientificStat += 4;
			break;
		default:
			break;
		}

		switch (Motive)
		{
		case EDAMotive::DAMotive_None:
			break;
		case EDAMotive::DAMotive_Duty:
			HealthStat += 2;
			StaminaStat += 2;
			DamageStat -= 0;
			PracticalStat -= 1;
			ScientificStat -= 3;
			SpiritualStat += 0;
			break;
		case EDAMotive::DAMotive_Glory:
			HealthStat -= 1;
			StaminaStat += 1;
			DamageStat += 3;
			PracticalStat -= 2;
			ScientificStat -= 2;
			SpiritualStat += 1;
			break;
		case EDAMotive::DAMotive_Profit:
			HealthStat += 2;
			StaminaStat -= 2;
			DamageStat -= 1;
			PracticalStat += 3;
			ScientificStat += 1;
			SpiritualStat -= 3;
			break;
		case EDAMotive::DAMotive_Power:
			HealthStat += 2;
			StaminaStat -= 2;
			DamageStat += 2;
			PracticalStat += 1;
			ScientificStat += 1;
			SpiritualStat += 1;
			break;
		default:
			break;
		}

		Reset();
	}

	void Reset()
	{
		MaxHealth = 10.f * HealthStat;
		CurHealth = MaxHealth;

		MaxStamina = 10.f * StaminaStat;
		CurStamina = MaxStamina;
	}

	int GetLevel() const
	{
		return HealthStat + StaminaStat + DamageStat + PracticalStat + ScientificStat + SpiritualStat - 59;
	}


	bool HasSufficientStamina(float amount) const
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

	void AdjustCurrentHealth(float amount)
	{
		CurHealth = FMath::Clamp<float>(CurHealth + amount, 0.f, MaxHealth);
	}

	static FString GetClassTextFromWorldviewAndMotive(EDAWorldview WorldView, EDAMotive Motive)
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

	static int GetCostForLevel(int Level)
	{
		// TODO: Come up with a balanced formula for this
		return Level * 100;
	}
};