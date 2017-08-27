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
	float GetCurrentSpeed();

	UFUNCTION()
	void SetInputDirection(FVector Input);

	UFUNCTION()
	void SetIsRunning(bool ShouldRun);

	UFUNCTION()
	void TryRoll();

	UFUNCTION()
	void TryAttack();

	UFUNCTION(BlueprintCallable)
	void GetHit(float Damage);    // Set the incoming damage from the weapon hit and trigger animation

	UFUNCTION(BlueprintCallable)
	void TriggerIncomingDamage();	// Actually apply the incoming damage, called from animation blueprint

	UFUNCTION()
	void ToggleLock();

	UFUNCTION(BlueprintPure)
	float GetStrafeValue();

	UFUNCTION(BlueprintPure)
	float GetApproachValue();

	UFUNCTION(BlueprintPure)
	float GetCurrentHealthPercent();

	UFUNCTION(BlueprintPure)
	float GetCurrentStaminaPercent();

	UFUNCTION(BlueprintCallable)
	void ConsumeStamina(float Amount);

	UFUNCTION(BlueprintPure)
	FORCEINLINE FDACharacterAttributes GetAttributes() { return Attributes; };

	UFUNCTION(BlueprintPure)
	FORCEINLINE class ADAWeaponBase* const GetEquippedWeapon() { return Weapon; };

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

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

	UPROPERTY()
	bool TakingDamage;

	UPROPERTY()
	bool IsDead;

	UPROPERTY()
	float StaminaBuffer;

	UPROPERTY()
	FDACharacterAttributes Attributes;

	UPROPERTY(EditAnywhere)
	class ADACharacter* TargetEnemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class ADAWeaponBase* Weapon;

	UPROPERTY()
	float IncomingDamage;

	UPROPERTY()
	class UDAPlayerAnimInstance* Animation;

	UPROPERTY()
	float StrafeValue;

	UPROPERTY()
	float ApproachValue; 

	void StandardMotion(float DeltaTime);

	void LockedMotion(float DeltaTime);
	
};
