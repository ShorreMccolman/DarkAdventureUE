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
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void Pursue(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void NoticePlayer(class ADAPlayer* Player);

	UFUNCTION(BlueprintCallable)
	void LosePlayer(class ADAPlayer* Player);
	
};
