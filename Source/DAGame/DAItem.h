// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DAItem.generated.h"

UENUM(BlueprintType)
enum class EDAItemType : uint8
{
	DAItemType_Consumable UMETA(DisplayName = "Consumable"),
	DAItemType_Weapon UMETA(DisplayName = "Weapon"),
	DAItemType_Armour UMETA(DisplayName = "Armour")
};

/**
 * 
 */
UCLASS(Blueprintable)
class UDAItem : public UObject
{
	GENERATED_BODY()

public:
	UDAItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EDAItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* ObjClass;
};
