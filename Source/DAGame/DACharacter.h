// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DACharacterAttributes.h"
#include "DAInventorySystem.h"
#include "DACombatSystem.h"
#include "DACharacter.generated.h"

UCLASS()
class DAGAME_API ADACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADACharacter();

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
	FORCEINLINE FDACharacterAttributes GetAttributes() const { return Attributes; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE FDACharacterVitals GetVitals() const { return Vitals; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetCurrentSouls() const { return Vitals.CurrentSouls; }

	UFUNCTION(BlueprintPure)
	class UDAGeneratedAttributes* GetGeneratedAttributes() const;

	UFUNCTION(BlueprintCallable)
	void RegenerateAttributes();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	UFUNCTION(BlueprintCallable)
	void SetCharacterRotationLock(bool Lock);

	UFUNCTION(BlueprintCallable)
	void GainSouls(int Amount);

	UFUNCTION(BlueprintCallable)
	void ConsumeSouls(int Amount);

	UFUNCTION(BlueprintCallable)
	void HealCharacter(float Amount);

	UFUNCTION(BlueprintCallable)
	void ConsumeStamina(float Amount);

	UFUNCTION(BlueprintCallable)
	void GetHit(FDAWeaponPayload Payload);    // Set the incoming damage from the weapon hit and trigger animation

	UFUNCTION(BlueprintCallable)
	void ExecuteAttack();

	UFUNCTION(BlueprintCallable)
	void ExecuteStrongAttack();

	UFUNCTION(BlueprintCallable)
	virtual void TriggerIncomingDamage();	// Actually apply the incoming damage, called from animation blueprint

	UFUNCTION(BlueprintCallable)
	void AddPotentialTarget(class ADACharacter *Target);

	UFUNCTION(BlueprintCallable)
	void RemovePotentialTarget(class ADACharacter* Target);

	UFUNCTION(BlueprintCallable)
	void UpdateAttributes(FDACharacterAttributes NewAttributes);

	UFUNCTION(BlueprintCallable)
	void SetNewOrigin(FVector Position, FName RegionName);

	/**********************
	
	INVENTORY AND EQUIPMENT

	**********************/

	UFUNCTION(BlueprintCallable)
	void UseHealItem();

	UFUNCTION(BlueprintCallable)
	void UseQueuedItem();

	UFUNCTION(BlueprintCallable)
	void UseConsumableItem(FDAInventoryItem InventoryItem);

	UFUNCTION(BlueprintCallable)
	void FireProjectile();

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(FName ID, FName SocketName);

	UFUNCTION(BlueprintCallable)
	void EquipWeaponItem(FDAInventoryItemDataPair Pair, FName SocketName);

	UFUNCTION(BlueprintCallable)
	void EquipSecondaryWeapon(FName ID, FName SocketName);

	UFUNCTION(BlueprintCallable)
	void EquipItemToSlot(FDAInventoryItem Item, EDAEquipmentSlot Slot);

	UFUNCTION(BlueprintCallable)
	void RemoveItemFromSlot(FDAInventoryItem Item, EDAEquipmentSlot Slot);

	UFUNCTION(BlueprintCallable)
	void DiscardQuantityOfItem(FDAInventoryItem Item, int Quantity);

	UFUNCTION(BlueprintCallable)
	class UDAItem* GetEquippedItemInSlot(EDAEquipmentSlot Slot) const;

	UFUNCTION(BlueprintCallable)
	FDAInventoryItemDataPair GetEquippedPairInSlot(EDAEquipmentSlot Slot);

	UFUNCTION(BlueprintPure)
	FORCEINLINE FDACharacterInventory GetInventory() const { return Inventory; };

	UFUNCTION(BlueprintPure)
	FORCEINLINE TArray<FDAInventoryItem> GetInventoryItems() const { return Inventory.Items; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE class ADAWeaponBase* GetEquippedWeapon() const { return Weapon; };

	/*******************
	
	CHARACTER MOVEMENT
	
	*******************/

	void SetInputDirection(FVector Input);

	void SetIsRunning(bool ShouldRun);

	UFUNCTION()
	FORCEINLINE bool IsTargetLocked() const { return bIsTargetLocked; }

	void ToggleLock();

	void TryRoll();

	void TryAttack();

	void TryStrongAttack();

	void TryHeal();

	void TryUse();

	void TryConsumable(EDAEquipmentSlot Slot);

	virtual void Reset();

	virtual void ShowDetails(bool ShouldShow);

	virtual void ShowTarget(bool ShouldTarget);

protected:
	UPROPERTY(EditAnywhere, Category = Motor)
	float WalkSpeed;

	UPROPERTY(EditAnywhere, Category = Motor)
	float Acceleration;

	UPROPERTY(EditAnywhere, Category = Motor)
	float Decceleration;

	UPROPERTY(EditAnywhere, Category = Motor)
	float TurnRate;

	bool bIsRunning;

	bool bIsTargetLocked;

	bool bShouldLockRotation;

	bool bIsTakingDamage;

	bool bIsDead;

	float IncomingDamage;

	FVector InputDirection;

	FVector TargetDirection;

	FDACharacterVitals Vitals;

	FDACharacterAttributes Attributes;

	FDACharacterInventory Inventory;

	FVector OriginLocation;

	FName OriginRegion;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	virtual void OnCharacterDeath();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNavigationSystem* NavSystem;

	UPROPERTY(EditAnywhere)
	class ADACharacter* TargetEnemy;

	UPROPERTY()
	TArray<class ADACharacter*> PotentialTargets;

	UPROPERTY()
	class ADAWeaponBase* Weapon;

	UPROPERTY()
	class ADAWeaponBase* Weapon2;

	UPROPERTY()
	class UDAPlayerAnimInstance* Animation;

	UPROPERTY()
	class UDAGeneratedAttributes* GeneratedAttributes;


	void UpdateBestTarget();

	void FaceTargetDirection(FVector Target, float angle, float DeltaTime);

	void StandardMotion(float DeltaTime);

	void LockedMotion(float DeltaTime);

	void Pursue(float Distance, float DeltaTime);

	void HoldPosition(float DeltaTime);

	void SetIsLocked(bool ShouldLock);

private:
	float Speed;

	float StrafeValue;

	float ApproachValue;

	float StaminaBuffer;

	UPROPERTY()
	FDAInventoryItemDataPair QueuedItem;
	
};
