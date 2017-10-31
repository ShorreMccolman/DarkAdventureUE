#pragma once

#include "CoreMinimal.h"
#include "DAItemManager.h"
#include "DAItem.h"
#include "DAConsumableItem.h"
#include "DAWeaponItem.h"
#include "DAArmourItem.h"
#include "DARingItem.h"
#include "DAKeyItem.h"
#include "DACharacterAttributes.h"
#include "DAInventorySystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemButtonConfirmAction, UDAItemButton*, Button);

UENUM(BlueprintType)
enum class EDAEquipmentSlot : uint8
{
	EDAEquipmentSlot_None = 0 UMETA(DisplayName = "None"),
	EDAEquipmentSlot_RightHand = 1 UMETA(DisplayName = "Right Hand"),
	EDAEquipmentSlot_LeftHand = 2 UMETA(DisplayName = "Left Hand"),
	EDAEquipmentSlot_ArmourSet = 11 UMETA(DisplayName = "Armour Set"),
	EDAEquipmentSlot_Ring1 = 21 UMETA(DisplayName = "Ring1"),
	EDAEquipmentSlot_Ring2 = 22 UMETA(DisplayName = "Ring2"),
	EDAEquipmentSlot_Ring3 = 23 UMETA(DisplayName = "Ring3"),
	EDAEquipmentSlot_Ring4 = 24 UMETA(DisplayName = "Ring4"),
	EDAEquipmentSlot_Consumable1 = 31 UMETA(DisplayName = "Consumable1 (Up)"),
	EDAEquipmentSlot_Consumable2 = 32 UMETA(DisplayName = "Consumable2 (Down)"),
	EDAEquipmentSlot_Consumable3 = 33 UMETA(DisplayName = "Consumable3 (Left)"),
	EDAEquipmentSlot_Consumable4 = 34 UMETA(DisplayName = "Consumable4 (Right)")
};

USTRUCT(BlueprintType)
struct FDAGenericItem
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FName ID;

	UPROPERTY(BlueprintReadWrite)
	FString InstanceID;
};

USTRUCT(BlueprintType)
struct FDAEquipmentItem : public FDAGenericItem
{
	GENERATED_BODY()

	FDAEquipmentItem()
	{
		ID = "";
	}

	FDAEquipmentItem(FName ItemID, FString ItemInstanceID)
	{
		ID = ItemID;
		InstanceID = ItemInstanceID;
	}
};

USTRUCT(BlueprintType)
struct FDAInventoryItem : public FDAGenericItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Quantity;

	UPROPERTY(BlueprintReadWrite)
	TArray<FName> Modifications;

	FDAInventoryItem()
	{
		ID = "";
		InstanceID = "";
		Quantity = 0;
	}

	FDAInventoryItem(FName ItemID, int Quantity)
		: Quantity(Quantity)
	{
		ID = ItemID;

		FGuid guid = FGuid::NewGuid();
		InstanceID = guid.ToString();
	}

	FDAInventoryItem(FName ItemID, FString ItemInstanceID, int Quantity)
		: Quantity(Quantity)
	{
		ID = ItemID;
		InstanceID = ItemInstanceID;
	}
};

USTRUCT(BlueprintType)
struct FDAInventoryItemDataPair
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FDAInventoryItem Item;

	UPROPERTY(BlueprintReadWrite)
	UDAItem* Data;

	UPROPERTY(BlueprintReadWrite)
	bool bIsValidItem;

	UPROPERTY(BlueprintReadWrite)
	bool bIsEquipped;


	FDAInventoryItemDataPair()
	{
		Item = FDAInventoryItem();
		Data = nullptr;
		bIsValidItem = false;
		bIsEquipped = false;
	}


	FDAInventoryItemDataPair(FDAInventoryItem InventoryItem, UDAItem* ItemData)
		: Item(InventoryItem), Data(ItemData)
	{
		bIsValidItem = ItemData != nullptr;
		bIsEquipped = false;
	}

};

USTRUCT(BlueprintType)
struct FDACharacterEquipment
{
	GENERATED_BODY()

	UPROPERTY()
	FDAEquipmentItem RightHand;

	UPROPERTY()
	FDAEquipmentItem LeftHand;

	UPROPERTY()
	FDAEquipmentItem ArmorSet;

	UPROPERTY()
	FDAEquipmentItem Ring1;

	UPROPERTY()
	FDAEquipmentItem Ring2;

	UPROPERTY()
	FDAEquipmentItem Ring3;

	UPROPERTY()
	FDAEquipmentItem Ring4;

	UPROPERTY()
	FDAEquipmentItem Consumable1;

	UPROPERTY()
	FDAEquipmentItem Consumable2;

	UPROPERTY()
	FDAEquipmentItem Consumable3;

	UPROPERTY()
	FDAEquipmentItem Consumable4;

	void EquipToRightHand(FName ID, FString InstanceID)
	{
		RightHand = FDAEquipmentItem(ID, InstanceID);
	}

	void EquipToLeftHand(FName ID, FString InstanceID)
	{
		LeftHand = FDAEquipmentItem(ID, InstanceID);
	}

	void EquipToRing1(FName ID, FString InstanceID)
	{
		Ring1 = FDAEquipmentItem(ID, InstanceID);
	}

	void EquipToRing2(FName ID, FString InstanceID)
	{
		Ring2 = FDAEquipmentItem(ID, InstanceID);
	}

	void EquipToRing3(FName ID, FString InstanceID)
	{
		Ring3 = FDAEquipmentItem(ID, InstanceID);
	}

	void EquipToRing4(FName ID, FString InstanceID)
	{
		Ring4 = FDAEquipmentItem(ID, InstanceID);
	}

	void EquipToArmourSet(FName ID, FString InstanceID)
	{
		ArmorSet = FDAEquipmentItem(ID, InstanceID);
	}

	void EquipToConsumable1(FName ID, FString InstanceID)
	{
		Consumable1 = FDAEquipmentItem(ID, InstanceID);
	}

	void EquipToConsumable2(FName ID, FString InstanceID)
	{
		Consumable2 = FDAEquipmentItem(ID, InstanceID);
	}

	void EquipToConsumable3(FName ID, FString InstanceID)
	{
		Consumable3 = FDAEquipmentItem(ID, InstanceID);
	}

	void EquipToConsumable4(FName ID, FString InstanceID)
	{
		Consumable4 = FDAEquipmentItem(ID, InstanceID);
	}

	bool InstanceIDIsEquipped(FString ID)
	{
		bool IsEquipped = false;
		if (RightHand.InstanceID.Equals(ID))
			IsEquipped = true;
		if (LeftHand.InstanceID.Equals(ID))
			IsEquipped = true;
		if (Ring1.InstanceID.Equals(ID))
			IsEquipped = true;
		if (Ring2.InstanceID.Equals(ID))
			IsEquipped = true;
		if (Ring3.InstanceID.Equals(ID))
			IsEquipped = true;
		if (Ring4.InstanceID.Equals(ID))
			IsEquipped = true;
		if (ArmorSet.InstanceID.Equals(ID))
			IsEquipped = true;
		if (Consumable1.InstanceID.Equals(ID))
			IsEquipped = true;
		if (Consumable2.InstanceID.Equals(ID))
			IsEquipped = true;
		if (Consumable3.InstanceID.Equals(ID))
			IsEquipped = true;
		if (Consumable4.InstanceID.Equals(ID))
			IsEquipped = true;

		return IsEquipped;
	}
};

USTRUCT(BlueprintType)
struct FDACharacterInventory
{
	GENERATED_BODY()

	UPROPERTY()
	FDACharacterEquipment Equipment;

	UPROPERTY()
	FDAInventoryItem Heals;

	UPROPERTY()
	TArray<FDAInventoryItem> Items;

	void SetupAsNewPlayerInventory(FDACharacterAttributes Attributes, UDAItemManager* ItemManager)
	{
		Heals = FDAInventoryItem("Heal", 5);

		AddItem("Token", ItemManager, 5);

		switch (Attributes.WorldView)
		{
		case EDAWorldview::DAWorldView_Spritual:
			AddItemAndEquip("Chain", ItemManager, EDAEquipmentSlot::EDAEquipmentSlot_ArmourSet);
			break;
		case EDAWorldview::DAWorldView_Practical:
			AddItemAndEquip("Leather", ItemManager, EDAEquipmentSlot::EDAEquipmentSlot_ArmourSet);
			break;
		case EDAWorldview::DAWorldView_Scientific:
			AddItemAndEquip("Cloth", ItemManager, EDAEquipmentSlot::EDAEquipmentSlot_ArmourSet);
			break;
		default:
			break;
		}

		switch (Attributes.Motive)
		{
		case EDAMotive::DAMotive_Duty:
			AddItemAndEquip("Sword", ItemManager, EDAEquipmentSlot::EDAEquipmentSlot_RightHand);
			break;
		case EDAMotive::DAMotive_Glory:
			AddItemAndEquip("Hammer", ItemManager, EDAEquipmentSlot::EDAEquipmentSlot_RightHand);
			break;
		case EDAMotive::DAMotive_Profit:
			AddItemAndEquip("Crossbow", ItemManager, EDAEquipmentSlot::EDAEquipmentSlot_RightHand);
			break;
		case EDAMotive::DAMotive_Power:
			AddItemAndEquip("Sword", ItemManager, EDAEquipmentSlot::EDAEquipmentSlot_RightHand);
			break;
		default:
			break;
		}

		TArray<FName> Names = ItemManager->GetAllIDs();
		for (auto Name : Names) {
			AddItem(Name, ItemManager, 1);
		}
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

	FString AddItem(FName ID, UDAItemManager* ItemManager, int quantity) 
	{
		UDAItem* Item = ItemManager->GetItemByID(ID);
		if (Item) {
			return AddItem(ID, *Item, quantity);
		}
		return "";
	}

	FString AddItem(FName ID, UDAItem& ItemData, int quantity) 
	{
		if (ItemData.MaxQuantity == 0) {
			FDAInventoryItem New = FDAInventoryItem(ID, 1);
			Items.Add(New);
			return New.InstanceID;
		}
		else {
			FDAInventoryItem *Item = Items.FindByPredicate([ID](const FDAInventoryItem& Item) {
				return Item.ID == ID;
			});
			if (Item) {
				Item->Quantity = FMath::Min(Item->Quantity + quantity, ItemData.MaxQuantity);
				return Item->InstanceID;
			} else {
				FDAInventoryItem New = FDAInventoryItem(ID, FMath::Min(quantity, ItemData.MaxQuantity));
				Items.Add(New);
				return New.InstanceID;
			}
		}
		return "";
	}

	int RemoveQuantityOfInstanceItem(FString InstanceID, int Quantity = 1)
	{
		int32 ItemIndex = INDEX_NONE;
		ItemIndex = Items.IndexOfByPredicate([InstanceID](const FDAInventoryItem& Item) {
			return Item.InstanceID.Equals(InstanceID);
		});

		if (ItemIndex != INDEX_NONE) {
			if (Items[ItemIndex].Quantity > Quantity) {
				Items[ItemIndex].Quantity -= Quantity;
				return Items[ItemIndex].Quantity;
			}
			else {
				Items.RemoveAt(ItemIndex);
			}
		}
		return 0;
	}

	void EquipItem(FName ID, FString InstanceID, EDAEquipmentSlot Slot)
	{
		switch (Slot)
		{
		case EDAEquipmentSlot::EDAEquipmentSlot_RightHand:
			Equipment.EquipToRightHand(ID, InstanceID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_LeftHand:
			Equipment.EquipToLeftHand(ID, InstanceID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Ring1:
			Equipment.EquipToRing1(ID, InstanceID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Ring2:
			Equipment.EquipToRing2(ID, InstanceID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Ring3:
			Equipment.EquipToRing3(ID, InstanceID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Ring4:
			Equipment.EquipToRing4(ID, InstanceID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_ArmourSet:
			Equipment.EquipToArmourSet(ID, InstanceID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Consumable1:
			Equipment.EquipToConsumable1(ID, InstanceID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Consumable2:
			Equipment.EquipToConsumable2(ID, InstanceID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Consumable3:
			Equipment.EquipToConsumable3(ID, InstanceID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Consumable4:
			Equipment.EquipToConsumable4(ID, InstanceID);
			break;
		default:
			break;
		}
	}

	void UnequipItem(FString InstanceID, EDAEquipmentSlot Slot)
	{
		FName ID = "";
		switch (Slot)
		{
		case EDAEquipmentSlot::EDAEquipmentSlot_RightHand:
			Equipment.EquipToRightHand(ID,"");
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_LeftHand:
			Equipment.EquipToLeftHand(ID, "");
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Ring1:
			Equipment.EquipToRing1(ID, "");
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Ring2:
			Equipment.EquipToRing2(ID, "");
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Ring3:
			Equipment.EquipToRing3(ID, "");
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Ring4:
			Equipment.EquipToRing4(ID, "");
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_ArmourSet:
			Equipment.EquipToArmourSet(ID, "");
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Consumable1:
			Equipment.EquipToConsumable1(ID, "");
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Consumable2:
			Equipment.EquipToConsumable2(ID, "");
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Consumable3:
			Equipment.EquipToConsumable3(ID, "");
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Consumable4:
			Equipment.EquipToConsumable4(ID, "");
			break;
		default:
			break;
		}
	}

	void AddItemAndEquip(FName ID, UDAItemManager* ItemManager, EDAEquipmentSlot Slot)
	{
		FString InstanceID = AddItem(ID, ItemManager, 1);
		EquipItem(ID, InstanceID, Slot);
	}

	FDAInventoryItemDataPair GetItemDataPairInSlot(const UDAItemManager& ItemManager, EDAEquipmentSlot Slot)
	{
		UDAItem* Item = nullptr;
		FName ID = "";
		FString InstanceID = "";
		switch (Slot)
		{
		case EDAEquipmentSlot::EDAEquipmentSlot_RightHand:
			ID = Equipment.RightHand.ID;
			InstanceID = Equipment.RightHand.InstanceID;
			Item = ItemManager.GetItemByID(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_LeftHand:
			ID = Equipment.LeftHand.ID;
			InstanceID = Equipment.LeftHand.InstanceID;
			Item = ItemManager.GetItemByID(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Ring1:
			ID = Equipment.Ring1.ID;
			InstanceID = Equipment.Ring1.InstanceID;
			Item = ItemManager.GetItemByID(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Ring2:
			ID = Equipment.Ring2.ID;
			InstanceID = Equipment.Ring2.InstanceID;
			Item = ItemManager.GetItemByID(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Ring3:
			ID = Equipment.Ring3.ID;
			InstanceID = Equipment.Ring3.InstanceID;
			Item = ItemManager.GetItemByID(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Ring4:
			ID = Equipment.Ring4.ID;
			InstanceID = Equipment.Ring4.InstanceID;
			Item = ItemManager.GetItemByID(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_ArmourSet:
			ID = Equipment.ArmorSet.ID;
			InstanceID = Equipment.ArmorSet.InstanceID;
			Item = ItemManager.GetItemByID(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Consumable1:
			ID = Equipment.Consumable1.ID;
			InstanceID = Equipment.Consumable1.InstanceID;
			Item = ItemManager.GetItemByID(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Consumable2:
			ID = Equipment.Consumable2.ID;
			InstanceID = Equipment.Consumable2.InstanceID;
			Item = ItemManager.GetItemByID(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Consumable3:
			ID = Equipment.Consumable3.ID;
			InstanceID = Equipment.Consumable3.InstanceID;
			Item = ItemManager.GetItemByID(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Consumable4:
			ID = Equipment.Consumable4.ID;
			InstanceID = Equipment.Consumable4.InstanceID;
			Item = ItemManager.GetItemByID(ID);
			break;
		default:
			break;
		}

		FDAInventoryItem InventoryItem = FDAInventoryItem(ID, InstanceID, GetItemQuantity(ID));
		if (Item) {
			return FDAInventoryItemDataPair(InventoryItem, Item);
		}
		else {
			return FDAInventoryItemDataPair();
		}
	}

	UDAItem* GetItemInSlot(UDAItemManager* ItemManager, EDAEquipmentSlot Slot) const
	{
		UDAItem* Item = nullptr;
		switch (Slot)
		{
		case EDAEquipmentSlot::EDAEquipmentSlot_RightHand:
			Item = ItemManager->GetItemByID(Equipment.RightHand.ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_LeftHand:
			Item = ItemManager->GetItemByID(Equipment.LeftHand.ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Ring1:
			Item = ItemManager->GetItemByID(Equipment.Ring1.ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Ring2:
			Item = ItemManager->GetItemByID(Equipment.Ring2.ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Ring3:
			Item = ItemManager->GetItemByID(Equipment.Ring3.ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Ring4:
			Item = ItemManager->GetItemByID(Equipment.Ring4.ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_ArmourSet:
			Item = ItemManager->GetItemByID(Equipment.ArmorSet.ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Consumable1:
			Item = ItemManager->GetItemByID(Equipment.Consumable1.ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Consumable2:
			Item = ItemManager->GetItemByID(Equipment.Consumable2.ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Consumable3:
			Item = ItemManager->GetItemByID(Equipment.Consumable3.ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Consumable4:
			Item = ItemManager->GetItemByID(Equipment.Consumable4.ID);
			break;
		default:
			break;
		}
		return Item;
	}
};

