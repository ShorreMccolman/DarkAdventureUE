// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DACharacterAttributes.h"
#include "DAPlayerProfile.generated.h"

/**
 * 
 */
UCLASS()
class UDAPlayerProfile : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FString ID;

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	int Level;

	UPROPERTY()
	EDAWorldview Worldview;

	UPROPERTY()
	EDAMotive Motive;

	UFUNCTION(BlueprintPure)
	FORCEINLINE FString GetPlayerID() const { return ID; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE FString GetPlayerName() const { return PlayerName; }

	UFUNCTION(BlueprintCallable)
	class UTexture2D* GetIcon() const;
	
};
