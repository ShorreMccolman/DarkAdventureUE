// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DAMasterSettings.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API UDAMasterSettings : public USaveGame
{
	GENERATED_BODY()
	
public:
	UDAMasterSettings();

	UPROPERTY()
	bool bHasCharacter;

	UPROPERTY()
	bool bHasCurrentCharacter;

	UPROPERTY()
	FString CurrentCharacterID;

	UPROPERTY()
	TArray<FString> CharacterIDs;

	UFUNCTION()
	void SetCurrentCharacter(FString ID);

	UFUNCTION()
	void ClearCurrentCharacter();
	
	
};
