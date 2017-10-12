// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAItem.h"
#include "DAKeyItem.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API UDAKeyItem : public UDAItem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE FText GetItemEffectDescription() const { return EffectDescription; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
	FText EffectDescription;
	
};
