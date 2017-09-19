// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DACharacterAttributes.h"
#include "DAPlayerSave.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API UDAPlayerSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	FDACharacterAttributes Attributes;

	UPROPERTY()
	FDACharacterInventory Inventory;

	UPROPERTY()
	FVector Position;

	UPROPERTY()
	FRotator Facing;

	UPROPERTY()
	bool bIsNewPlayer;
	
	
};
