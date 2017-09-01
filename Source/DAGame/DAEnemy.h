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

	UFUNCTION(BlueprintCallable)
	virtual void ShowDetails(bool ShouldShow) override;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnCharacterDeath() override;

	UFUNCTION(BlueprintCallable)
	void NoticePlayer(class ADAPlayer* Player);

	UFUNCTION(BlueprintCallable)
	void LosePlayer(class ADAPlayer* Player);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=DisplayDetails)
	class UWidgetComponent* HealthBar;
	
};
