// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAItem.h"
#include "DAConsumableItem.generated.h"

/**
 * 
 */
UCLASS()
class UDAConsumableItem : public UDAItem
{
	GENERATED_BODY()

public:
	UDAConsumableItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDAConsumableType ConsumableType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
	FText EffectDescription;

	UFUNCTION(BlueprintPure)
	FORCEINLINE FString GetConsumableTypeDescription() const {
		switch (ConsumableType)
		{
		case EDAConsumableType::DAConsumableType_SingleUse:
			return "Single Use";
		case EDAConsumableType::DAConsumableType_UnlimitedUse:
			return "Unlimited Use";
		default:
			return "";
		}
	}

	UFUNCTION(BlueprintPure)
	FORCEINLINE FText GetItemEffectDescription() const { return EffectDescription; }
	
};
