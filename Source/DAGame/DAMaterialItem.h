// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAItem.h"
#include "DAMaterialItem.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API UDAMaterialItem : public UDAItem
{
	GENERATED_BODY()
	
public:
	UDAMaterialItem();

	UFUNCTION(BlueprintPure)
	FORCEINLINE FText GetItemEffectDescription() const { return EffectDescription; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
	FText EffectDescription;
	
};
