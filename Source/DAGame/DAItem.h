// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DACharacterAttributes.h"
#include "DAItem.generated.h"

UENUM(BlueprintType)
enum class EDAScalingFactor : uint8
{
	DAScalingFactor_None UMETA(DisplayName = "None"),
	DAScalingFactor_A UMETA(DisplayName = "A class"),
	DAScalingFactor_B UMETA(DisplayName = "B class"),
	DAScalingFactor_C UMETA(DisplayName = "C class"),
	DAScalingFactor_D UMETA(DisplayName = "D class")
};

UENUM(BlueprintType)
enum class EDAConsumableType : uint8
{
	DAConsumableType_SingleUse UMETA(DisplayName = "Single Use Item"),
	DAConsumableType_MultiUse UMETA(DisplayName = "Multi Use Item"),
	DAConsumableType_UnlimitedUse UMETA(DisplayName = "Unlimited Use Item"),
	DAConsumableType_NoUse UMETA(DisplayName = "Non Usable Consumable?")
};

UENUM(BlueprintType)
enum class EDAWeaponType : uint8
{
	DAWeaponType_OneHand UMETA(DisplayName = "One Handed Weapon"),
	DAWeaponType_TwoHand UMETA(DisplayName = "Two Handed Weapon"),
	DAWeaponType_Ranged UMETA(DisplayName = "Ranged Weapon")
};

UENUM(BlueprintType)
enum class EDAArmourType : uint8
{
	DAArmourType_Light UMETA(DisplayName = "Light Weight"),
	DAArmourType_Medium UMETA(Displayname = "Medium Weight"),
	DAArmourType_Heavy UMETA(DisplayName = "Heavy Weight")
};

UENUM(BlueprintType)
enum class EDAItemType : uint8
{
	DAItemType_Consumable UMETA(DisplayName = "Consumable"),
	DAItemType_Weapon UMETA(DisplayName = "Weapon"),
	DAItemType_Armour UMETA(DisplayName = "Armour"),
	DAItemType_Ring UMETA(DisplayName = "Ring"),
	DAItemType_Key UMETA(DisplayName = "Key Item"),
	DAItemType_Any UMETA(DisplayName = "None")
};

/**
 * 
 */
UCLASS(Blueprintable)
class UDAItem : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DisplayName;

	UPROPERTY(BlueprintReadOnly)
	EDAItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* ObjClass;

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetItemMaxQuantity() const { return MaxQuantity; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE EDAItemType GetItemType() const { return ItemType; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE FName GetItemDisplayName() const { return DisplayName; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE FText GetItemDescription() const { return ItemDescription; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE class UTexture2D* GetItemIcon() const { return Icon; }

	UFUNCTION(BlueprintCallable)
	static float ScalingFactorModifier(EDAScalingFactor Factor);
};
