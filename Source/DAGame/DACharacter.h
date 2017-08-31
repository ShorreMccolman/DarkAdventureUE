// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DACharacterAttributes.h"
#include "DACharacter.generated.h"

UCLASS()
class DAGAME_API ADACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADACharacter();

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

	UFUNCTION()
	void SetInputDirection(FVector Input);

	UFUNCTION()
	void SetIsRunning(bool ShouldRun);

	UFUNCTION(BlueprintCallable)
	void SetCharacterRotationLock(bool Lock);

	UFUNCTION()
	void TryRoll();

	UFUNCTION()
	void TryAttack();

	UFUNCTION()
	void TryStrongAttack();

	UFUNCTION(BlueprintCallable)
	void GetHit(float Damage);    // Set the incoming damage from the weapon hit and trigger animation

	UFUNCTION(BlueprintCallable)
	void TriggerIncomingDamage();	// Actually apply the incoming damage, called from animation blueprint

	UFUNCTION()
	void ToggleLock();

	UFUNCTION(BlueprintCallable)
	void ConsumeStamina(float Amount);

	UFUNCTION(BlueprintPure)
	FORCEINLINE FDACharacterAttributes GetAttributes() const { return Attributes; };

	UFUNCTION(BlueprintPure)
	FORCEINLINE class ADAWeaponBase* GetEquippedWeapon() const { return Weapon; };

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	virtual void OnCharacterDeath();

	UFUNCTION(BlueprintCallable)
	void AddPotentialTarget(class ADACharacter *Target);

	UFUNCTION(BlueprintCallable)
	void RemovePotentialTarget(class ADACharacter* Target);

	UPROPERTY(EditAnywhere, Category = Motor)
	float WalkSpeed;

	UPROPERTY(EditAnywhere, Category = Motor)
	float Acceleration;

	UPROPERTY(EditAnywhere, Category = Motor)
	float Decceleration;

	UPROPERTY(EditAnywhere, Category = Motor)
	float TurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Motor)
	float Speed;

	UPROPERTY()
	FVector InputDirection;

	UPROPERTY()
	FVector TargetDirection;

	UPROPERTY()
	bool Running;

	UPROPERTY()
	bool Locked;

	UPROPERTY(EditAnywhere)
	bool LockRotation;

	UPROPERTY()
	bool TakingDamage;

	UPROPERTY()
	bool IsDead;

	UPROPERTY()
	float StaminaBuffer;

	UPROPERTY()
	FDACharacterAttributes Attributes;

	UPROPERTY(BlueprintReadWrite)
	class ADACharacter* TargetEnemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<class ADACharacter*> PotentialTargets;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class ADAWeaponBase* Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* Collider;

	UPROPERTY()
	float IncomingDamage;

	UPROPERTY()
	class UDAPlayerAnimInstance* Animation;

	UPROPERTY()
	float StrafeValue;

	UPROPERTY()
	float ApproachValue; 

	void UpdateBestTarget();

	void FaceTargetDirection(FVector Target, float angle, float DeltaTime);

	void StandardMotion(float DeltaTime);

	void LockedMotion(float DeltaTime);

	void Pursue(float Distance, float DeltaTime);

	void HoldPosition(float DeltaTime);

	float InterpolateSpeed(float Current, float Target, float Acceleration, float DeltaTime);

	void SetIsLocked(bool ShouldLock);
	
};
