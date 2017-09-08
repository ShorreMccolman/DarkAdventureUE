// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DACharacterAttributes.h"
#include "DAWeaponBase.generated.h"

UCLASS()
class DAGAME_API ADAWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADAWeaponBase();

	UFUNCTION(BlueprintCallable)
	void DisableCollision();

	UFUNCTION(BlueprintCallable)
	void EnableCollision();

	UFUNCTION(BlueprintPure)
	float GetCurrentDamage(FDACharacterAttributes OwnerAttributes, FDACharacterAttributes TargetAttributes);

	UFUNCTION()
	void SetDAOwner(class ADACharacter* TheOwner);

	UFUNCTION()
	TSubclassOf<class UAnimInstance> GetAnimBP() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StrengthModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DexModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ADACharacter* DAOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<class UAnimInstance> AnimationBPClass;
	
};
