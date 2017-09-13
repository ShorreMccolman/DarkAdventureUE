#pragma once

#include "CoreMinimal.h"
#include "DAItemManager.h"
#include "DAItem.h"
#include "DACharacterAttributes.generated.h"

USTRUCT()
struct FDAInventoryItem
{
	GENERATED_BODY()

	UPROPERTY()
	FName ID;

	UPROPERTY()
	int Quantity;

	UPROPERTY()
	TArray<FName> Modifications;

	FDAInventoryItem()
	{
		ID = "";
		Quantity = 0;
	}

	FDAInventoryItem(FName ID, int Quantity)
		: ID(ID), Quantity(Quantity)
	{
		
	}
};

USTRUCT()
struct FDACharacterInventory
{
	GENERATED_BODY()

	UPROPERTY()
	FDAInventoryItem EquippedWeapon;

	UPROPERTY()
	FDAInventoryItem Heals;

	UPROPERTY()
	TArray<FDAInventoryItem> Items;

	FDACharacterInventory()
	{
		EquippedWeapon = FDAInventoryItem();
		Heals = FDAInventoryItem("Heal", 5);
	}

	void Reset()
	{
		Heals.Quantity = 5;
	}

	bool HasHeal()
	{
		return Heals.Quantity > 0;
	}

	void ConsumeHeal()
	{
		if (Heals.Quantity == 0) {
			UE_LOG(LogTemp, Warning, TEXT("Trying to consume heal with quantity 0"))
		}

		Heals.Quantity -= 1;
	}

	int GetItemQuantity(FName ID)
	{
		FDAInventoryItem *Item = Items.FindByPredicate([ID](const FDAInventoryItem& Item) {
			return Item.ID == ID;
		});
		if (Item) {
			return Item->Quantity;
		}

		return 0;
	}

	void AddItem(FName ID, UDAItem& ItemData, int quantity) {
		if (ItemData.MaxQuantity == 0) {
			Items.Add(FDAInventoryItem(ID, quantity));
		}
		else {
			FDAInventoryItem *Item = Items.FindByPredicate([ID](const FDAInventoryItem& Item) {
				return Item.ID == ID;
			});
			if (Item) {
				Item->Quantity = FMath::Min(Item->Quantity + quantity, ItemData.MaxQuantity);
				return;
			}
			Items.Add(FDAInventoryItem(ID, FMath::Min(quantity, ItemData.MaxQuantity)));
		}
	}
};

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
	int MaxHeals;

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

		MaxHeals = 5;

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
};