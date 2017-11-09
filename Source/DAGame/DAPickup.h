// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAInteractable.h"
#include "DAPickup.generated.h"

USTRUCT(BlueprintType)
struct FDALootDrop
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName ItemID;

	UPROPERTY(EditAnywhere)
	int Quantity;

	UPROPERTY(EditAnywhere)
	int Weight;

	FDALootDrop()
	{
		ItemID = "";
		Quantity = 0;
		Weight = 1;
	}

	FDALootDrop(FName ItemID, int Quantity, int Weight) : ItemID(ItemID), Quantity(Quantity), Weight(Weight)
	{

	}
};

USTRUCT(BlueprintType)
struct FDALootRolls
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChanceToDrop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDALootDrop> Drops;

	FDALootRolls()
	{
		
	}

	FDALootRolls(float ChanceToDrop, TArray<FDALootDrop> Drops) : ChanceToDrop(ChanceToDrop), Drops(Drops)
	{

	}
};

/**
 * 
 */
UCLASS()
class DAGAME_API ADAPickup : public ADAInteractable
{
	GENERATED_BODY()
	
public:
	ADAPickup();

	void Init(FName RegionID, bool IsCollected);

	void Uninit();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact();
	virtual void Interact_Implementation() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemDropID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DropQuantity;

	UFUNCTION(BlueprintImplementableEvent)
	void OpenPickupPopupEvent();

	UFUNCTION(BlueprintCallable)
	void SetupWithLootDrop(FDALootDrop Drop);

	UFUNCTION()
	FORCEINLINE FString GetInstanceID() const { return InstanceID; }

protected:
	UPROPERTY()
	bool IsInstance;

	UPROPERTY(VisibleAnywhere)
	FString InstanceID;

	UPROPERTY()
	FName RegionID;
	
};
