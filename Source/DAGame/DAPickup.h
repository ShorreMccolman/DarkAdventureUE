// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAInteractable.h"
#include "DAPickup.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API ADAPickup : public ADAInteractable
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	virtual void Interact() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemDropID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DropQuantity;

	UFUNCTION(BlueprintImplementableEvent)
	void OpenPickupPopupEvent();
	
};
