// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DACharacter.generated.h"

UCLASS()
class DAGAME_API ADACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
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
	void GetHit();

	UFUNCTION()
	void ToggleLock();

	UFUNCTION(BlueprintPure)
	float GetStrafeValue();

	UFUNCTION(BlueprintPure)
	float GetApproachValue();

	UFUNCTION(BlueprintPure)
	FORCEINLINE class ADAWeaponBase* const GetEquippedWeapon() { return Weapon; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
	class ADACharacter* TargetEnemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class ADAWeaponBase* Weapon;

	UPROPERTY()
	float StrafeValue;

	UPROPERTY()
	float ApproachValue; 

	void StandardMotion(float DeltaTime);

	void LockedMotion(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
