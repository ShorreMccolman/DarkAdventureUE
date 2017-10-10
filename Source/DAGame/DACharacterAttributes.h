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


USTRUCT(BlueprintType)
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
	int MaxHeals;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HealthStat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StaminaStat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DamageStat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PracticalStat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ScientificStat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SpiritualStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDAWorldview WorldView;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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
};