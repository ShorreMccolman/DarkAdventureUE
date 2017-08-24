// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DACharacter.h"
#include "DAPlayer.generated.h"

UCLASS()
class DAGAME_API ADAPlayer : public ADACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADAPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
};
