// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DACharacter.h"
#include "DAEnemy.generated.h"

UCLASS()
class DAGAME_API ADAEnemy : public ADACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADAEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
	
};
