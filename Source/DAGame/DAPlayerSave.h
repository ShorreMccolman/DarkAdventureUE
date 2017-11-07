// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DACharacterAttributes.h"
#include "DAInventorySystem.h"
#include "DARegionData.h"
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
	FString ID;

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	FDACharacterAttributes Attributes;

	UPROPERTY()
	FDACharacterInventory Inventory;

	UPROPERTY()
	FDACharacterVitals Vitals;

	UPROPERTY()
	TArray<FDARegionData> RegionData;

	UPROPERTY()
	FVector Position;

	UPROPERTY()
	FName CurrentRegion;

	UPROPERTY()
	FRotator Facing;

	UPROPERTY()
	FRotator CameraRotation;

	UPROPERTY()
	float CameraZoom;

	UPROPERTY()
	FVector HomePosition;

	UPROPERTY()
	FName HomeRegion;

	UPROPERTY()
	bool bIsNewPlayer;
};
