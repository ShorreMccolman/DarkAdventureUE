// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAItem.h"
#include "DARingItem.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API UDARingItem : public UDAItem
{
	GENERATED_BODY()
	
public:
	UDARingItem();

	UFUNCTION(BlueprintPure)
	FORCEINLINE FText GetItemEffectDescription() const { return EffectDescription; }

	virtual void ModifyGeneratedAttributes(class UDAGeneratedAttributes& Attributes) const override;

	UFUNCTION(BlueprintImplementableEvent)
	void ModifyAttributesEvent(class UDAGeneratedAttributes* Attributes) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
	FText EffectDescription;
	
	
};
