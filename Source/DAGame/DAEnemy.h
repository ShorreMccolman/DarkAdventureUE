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

	UFUNCTION()
	virtual void Reset() override;

	UFUNCTION()
	void ShowTarget(bool ShouldTarget) override;

	UFUNCTION(BlueprintCallable)
	virtual void ShowDetails(bool ShouldShow) override;

	UFUNCTION(BlueprintCallable)
	virtual void TriggerIncomingDamage() override;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnCharacterDeath() override;

	UFUNCTION(BlueprintCallable)
	void NoticePlayer(class ADAPlayer* Player);

	UFUNCTION(BlueprintCallable)
	void LosePlayer(class ADAPlayer* Player);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = DisplayDetails)
	class UWidgetComponent* Target;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=DisplayDetails)
	class UWidgetComponent* HealthBar;

	UPROPERTY(BlueprintReadWrite)
	float DamageLabelNumber;

	UPROPERTY()
	FTimerHandle DamageLabelTimerHandle;

	UFUNCTION()
	void ClearDamageLabelNumer();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateDetailsWidget();
	
};
