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

	TArray<FString> CharacterNames;
	
	
};
