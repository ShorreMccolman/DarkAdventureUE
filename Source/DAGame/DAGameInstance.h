// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DACharacterAttributes.h"
#include "DAGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API UDAGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void LoadMostRecentGame();

	UFUNCTION(BlueprintCallable)
	void TryLoadGame(FString PlayerName);

	UFUNCTION(BlueprintCallable)
	void TryCreateNewGame(FString PlayerName, FDACharacterAttributes Attributes);

	void CreatePlayerSave(FString PlayerName, FDACharacterAttributes Attributes);
	class UDAPlayerSave* LoadCurrentPlayerSave();
	
private:

	
};
