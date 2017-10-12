// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DACharacterAttributes.h"
#include "DAInventorySystem.h"
#include "DACharacter.generated.h"

UCLASS()
class DAGAME_API ADACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADACharacter();

protected:
	UPROPERTY(EditAnywhere, Category = Motor)
	float WalkSpeed;

	UPROPERTY(EditAnywhere, Category = Motor)
	float Acceleration;

	UPROPERTY(EditAnywhere, Category = Motor)
	float Decceleration;

	UPROPERTY(EditAnywhere, Category = Motor)
	float TurnRate;

public:
	UFUNCTION(BlueprintPure)
	float GetCurrentSpeed() const;

	UFUNCTION(BlueprintPure)
	float GetStrafeValue() const;

	UFUNCTION(BlueprintPure)
	float GetApproachValue() const;

	UFUNCTION(BlueprintPure)
	float GetCurrentHealthPercent() const;

	UFUNCTION(BlueprintPure)
	float GetCurrentStaminaPercent() const;

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetCurrentHeals() const { return Inventory.Heals.Quantity; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE FDACharacterAttributes GetAttributes() const { return Attributes; };

	UFUNCTION(BlueprintPure)
	FORCEINLINE FDACharacterInventory GetInventory() const { return Inventory; };

	UFUNCTION(BlueprintPure)
	FORCEINLINE TArray<FDAInventoryItem> GetInventoryItems() const { return Inventory.Items; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE class ADAWeaponBase* GetEquippedWeapon() const { return Weapon; };

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	UFUNCTION(BlueprintCallable)
	void SetCharacterRotationLock(bool Lock);

	UFUNCTION(BlueprintCallable)
	void UseHealItem();

	UFUNCTION(BlueprintCallable)
	void HealCharacter(float Amount);

	UFUNCTION(BlueprintCallable)
	void ConsumeStamina(float Amount);

	UFUNCTION(BlueprintCallable)
	void GetHit(float Damage);    // Set the incoming damage from the weapon hit and trigger animation

	UFUNCTION(BlueprintCallable)
	virtual void TriggerIncomingDamage();	// Actually apply the incoming damage, called from animation blueprint

	UFUNCTION(BlueprintCallable)
	void FireProjectile();

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(FName ID, FName SocketName);

	UFUNCTION(BlueprintCallable)
	void EquipSecondaryWeapon(FName ID, FName SocketName);

	UFUNCTION(BlueprintCallable)
	void AddPotentialTarget(class ADACharacter *Target);

	UFUNCTION(BlueprintCallable)
	void RemovePotentialTarget(class ADACharacter* Target);

	UFUNCTION(BlueprintCallable)
	class UDAItem* GetEquippedItemInSlot(EDAEquipmentSlot Slot);

	UFUNCTION(BlueprintCallable)
	FDAInventoryItemDataPair GetEquippedPairInSlot(EDAEquipmentSlot Slot);

	void SetInputDirection(FVector Input);

	void SetIsRunning(bool ShouldRun);

	void ToggleLock();

	void TryRoll();

	void TryAttack();

	void TryStrongAttack();

	void TryHeal();

	virtual void Reset();

	virtual void ShowDetails(bool ShouldShow);

	virtual void ShowTarget(bool ShouldTarget);

protected:
	bool bIsRunning;

	bool bIsTargetLocked;

	bool bShouldLockRotation;

	bool bIsTakingDamage;

	bool bIsDead;

	float IncomingDamage;

	FVector InputDirection;

	FVector TargetDirection;

	FVector Origin;

	FDACharacterAttributes Attributes;

	FDACharacterInventory Inventory;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	virtual void OnCharacterDeath();


	UPROPERTY()
	class ADACharacter* TargetEnemy;

	UPROPERTY()
	TArray<class ADACharacter*> PotentialTargets;

	UPROPERTY()
	class ADAWeaponBase* Weapon;

	UPROPERTY()
	class ADAWeaponBase* Weapon2;

	UPROPERTY()
	class UDAPlayerAnimInstance* Animation;


	void UpdateBestTarget();

	void FaceTargetDirection(FVector Target, float angle, float DeltaTime);

	void StandardMotion(float DeltaTime);

	void LockedMotion(float DeltaTime);

	void Pursue(float Distance, float DeltaTime);

	void HoldPosition(float DeltaTime);

	float InterpolateSpeed(float Current, float Target, float Acceleration, float DeltaTime);

	void SetIsLocked(bool ShouldLock);

private:
	float Speed;

	float StrafeValue;

	float ApproachValue;

	float StaminaBuffer;
	
};
