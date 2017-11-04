// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DACharacter.h"
#include "DAPickup.h"
#include "DAEnemy.generated.h"

USTRUCT(Blueprintable)
struct FDAEnemyAttributes
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MainWeaponLightDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MainWeaponStrongDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OffhandDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OffhandDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Defense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireResist;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ColdResist;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ElectricResist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SoulReward;
};

UCLASS()
class DAGAME_API ADAEnemy : public ADACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADAEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDAEnemyAttributes EnemyAttributes;

	UFUNCTION()
	virtual void Reset() override;

	UFUNCTION()
	void ShowTarget(bool ShouldTarget) override;

	UFUNCTION(BlueprintCallable)
	virtual void ShowDetails(bool ShouldShow) override;

	UFUNCTION(BlueprintCallable)
	virtual void TriggerIncomingDamage() override;

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnPickup(FDALootDrop Drop);

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDALootRolls> LootRolls;
	
	TArray<FDALootDrop> RollForLootDrops(const TArray<FDALootRolls>& Rolls) const;
};
