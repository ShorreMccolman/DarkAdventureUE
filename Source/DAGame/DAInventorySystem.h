#pragma once

#include "CoreMinimal.h"
#include "DAItemManager.h"
#include "DAItem.h"
#include "DACharacterAttributes.h"
#include "DAInventorySystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemButtonConfirmAction, UDAItemButton*, Button);

UENUM(BlueprintType)
enum class EDAEquipmentSlot : uint8
{
	EDAEquipmentSlot_None UMETA(DisplayName = "None"),
	EDAEquipmentSlot_RightHand UMETA(DisplayName = "Right Hand"),
	EDAEquipmentSlot_LeftHand UMETA(DisplayName = "Left Hand"),
	EDAEquipmentSlot_RightHandAlt UMETA(DisplayName = "Right Hand Alternate"),
	EDAEquipmentSlot_LeftHandAlt UMETA(DisplayName = "Left Hand Alternate"),
	EDAEquipmentSlot_ArmourSet UMETA(DisplayName = "Armour Set"),
	EDAEquipmentSlot_Consumable UMETA(DisplayName = "Consumable")
};

USTRUCT(BlueprintType)
struct FDAGenericItem
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FName ID;
};

USTRUCT(BlueprintType)
struct FDAEquipmentItem : public FDAGenericItem
{
	GENERATED_BODY()

	FDAEquipmentItem()
	{
		ID = "";
	}

	FDAEquipmentItem(FName ItemID)
	{
		ID = ItemID;
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
		Quantity = 0;
	}

	FDAInventoryItem(FName ItemID, int Quantity)
		: Quantity(Quantity)
	{
		ID = ItemID;
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


	FDAInventoryItemDataPair()
	{
		Item = FDAInventoryItem();
		Data = nullptr;
		bIsValidItem = false;
	}


	FDAInventoryItemDataPair(FDAInventoryItem InventoryItem, UDAItem* ItemData)
		: Item(InventoryItem), Data(ItemData)
	{
		bIsValidItem = ItemData != nullptr;
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
	FDAEquipmentItem RightHandAlt;

	UPROPERTY()
	FDAEquipmentItem LeftHandAlt;

	UPROPERTY()
	FDAEquipmentItem ArmorSet;

	UPROPERTY()
	FDAEquipmentItem Consumable;

	void EquipToRightHand(FName ID)
	{
		RightHand = FDAEquipmentItem(ID);
	}

	void EquipToLeftHand(FName ID)
	{
		LeftHand = FDAEquipmentItem(ID);
	}

	void EquipToRightHandAlt(FName ID)
	{
		RightHandAlt = FDAEquipmentItem(ID);
	}

	void EquipToLeftHandAlt(FName ID)
	{
		LeftHandAlt = FDAEquipmentItem(ID);
	}

	void EquipToArmourSet(FName ID)
	{
		ArmorSet = FDAEquipmentItem(ID);
	}

	void EquipToConsumable(FName ID)
	{
		Consumable = FDAEquipmentItem(ID);
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
			AddItemAndEquip("Sword", ItemManager, EDAEquipmentSlot::EDAEquipmentSlot_RightHand);
			break;
		case EDAMotive::DAMotive_Power:
			AddItemAndEquip("Sword", ItemManager, EDAEquipmentSlot::EDAEquipmentSlot_RightHand);
			break;
		default:
			break;
		}
		AddItem("Sword", ItemManager, 1);
		AddItem("Sword", ItemManager, 1);
		AddItem("Sword", ItemManager, 1);
		AddItem("Sword", ItemManager, 1);
		AddItem("Sword", ItemManager, 1);
		AddItem("Sword", ItemManager, 1);
		AddItem("Sword", ItemManager, 1);
		AddItem("Sword", ItemManager, 1);
		AddItem("Sword", ItemManager, 1);
		AddItem("Sword", ItemManager, 1);
		AddItem("Sword", ItemManager, 1);
		AddItem("Sword", ItemManager, 1);
		AddItem("Sword", ItemManager, 1);
		AddItem("Sword", ItemManager, 1);
		AddItem("Sword", ItemManager, 1);
		AddItem("Sword", ItemManager, 1);
		AddItem("Sword", ItemManager, 1);
		AddItem("Sword", ItemManager, 1);
		AddItem("Sword", ItemManager, 1);
		AddItem("Sword", ItemManager, 1);
		AddItem("Sword", ItemManager, 1);
		AddItem("Sword", ItemManager, 1);
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

	void AddItem(FName ID, UDAItemManager* ItemManager, int quantity) 
	{
		UDAItem* Item = ItemManager->GetItemByID(ID);
		if (Item) {
			AddItem(ID, *Item, quantity);
		}
	}

	void AddItem(FName ID, UDAItem& ItemData, int quantity) 
	{
		if (ItemData.MaxQuantity == 0) {
			Items.Add(FDAInventoryItem(ID, quantity));
		}
		else {
			FDAInventoryItem *Item = Items.FindByPredicate([ID](const FDAInventoryItem& Item) {
				return Item.ID == ID;
			});
			if (Item) {
				Item->Quantity = FMath::Min(Item->Quantity + quantity, ItemData.MaxQuantity);
			} else {
				Items.Add(FDAInventoryItem(ID, FMath::Min(quantity, ItemData.MaxQuantity)));
			}
		}
	}

	// Returns remaining quantity
	int RemoveItem(FName ID, int quantity = 1)
	{
		int32 ItemIndex = INDEX_NONE;
		ItemIndex = Items.IndexOfByPredicate([ID](const FDAInventoryItem& Item) {
			return Item.ID == ID;
		});

		if (ItemIndex != INDEX_NONE) {
			if (Items[ItemIndex].Quantity > quantity) {
				Items[ItemIndex].Quantity -= quantity;
				return Items[ItemIndex].Quantity;
			} else {
				Items.RemoveAt(ItemIndex);
			}
		}
		return 0;
	}

	void EquipItem(FName ID, EDAEquipmentSlot Slot)
	{
		switch (Slot)
		{
		case EDAEquipmentSlot::EDAEquipmentSlot_RightHand:
			Equipment.EquipToRightHand(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_LeftHand:
			Equipment.EquipToLeftHand(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_RightHandAlt:
			Equipment.EquipToRightHandAlt(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_LeftHandAlt:
			Equipment.EquipToLeftHandAlt(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_ArmourSet:
			Equipment.EquipToArmourSet(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Consumable:
			Equipment.EquipToConsumable(ID);
			break;
		default:
			break;
		}
	}

	void UnequipItem(EDAEquipmentSlot Slot)
	{
		FName ID = "";
		switch (Slot)
		{
		case EDAEquipmentSlot::EDAEquipmentSlot_RightHand:
			Equipment.EquipToRightHand(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_LeftHand:
			Equipment.EquipToLeftHand(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_RightHandAlt:
			Equipment.EquipToRightHandAlt(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_LeftHandAlt:
			Equipment.EquipToLeftHandAlt(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_ArmourSet:
			Equipment.EquipToArmourSet(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Consumable:
			Equipment.EquipToConsumable(ID);
			break;
		default:
			break;
		}
	}

	void AddItemAndEquip(FName ID, UDAItemManager* ItemManager, EDAEquipmentSlot Slot)
	{
		AddItem(ID, ItemManager, 1);
		EquipItem(ID, Slot);
	}

	FDAInventoryItemDataPair GetItemDataPairInSlot(const UDAItemManager& ItemManager, EDAEquipmentSlot Slot)
	{
		UDAItem* Item = nullptr;
		FName ID = "";
		switch (Slot)
		{
		case EDAEquipmentSlot::EDAEquipmentSlot_RightHand:
			ID = Equipment.RightHand.ID;
			Item = ItemManager.GetItemByID(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_LeftHand:
			ID = Equipment.LeftHand.ID;
			Item = ItemManager.GetItemByID(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_RightHandAlt:
			ID = Equipment.RightHandAlt.ID;
			Item = ItemManager.GetItemByID(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_LeftHandAlt:
			ID = Equipment.LeftHandAlt.ID;
			Item = ItemManager.GetItemByID(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_ArmourSet:
			ID = Equipment.ArmorSet.ID;
			Item = ItemManager.GetItemByID(ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Consumable:
			ID = Equipment.Consumable.ID;
			Item = ItemManager.GetItemByID(ID);
			break;
		default:
			break;
		}

		FDAInventoryItem InventoryItem = FDAInventoryItem(ID, GetItemQuantity(ID));
		if (Item) {
			return FDAInventoryItemDataPair(InventoryItem, Item);
		}
		else {
			return FDAInventoryItemDataPair();
		}
	}

	UDAItem* GetItemInSlot(UDAItemManager* ItemManager, EDAEquipmentSlot Slot)
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
		case EDAEquipmentSlot::EDAEquipmentSlot_RightHandAlt:
			Item = ItemManager->GetItemByID(Equipment.RightHandAlt.ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_LeftHandAlt:
			Item = ItemManager->GetItemByID(Equipment.LeftHandAlt.ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_ArmourSet:
			Item = ItemManager->GetItemByID(Equipment.ArmorSet.ID);
			break;
		case EDAEquipmentSlot::EDAEquipmentSlot_Consumable:
			Item = ItemManager->GetItemByID(Equipment.Consumable.ID);
			break;
		default:
			break;
		}
		return Item;
	}
};

