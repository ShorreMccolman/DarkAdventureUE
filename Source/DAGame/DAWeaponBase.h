// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DACharacterAttributes.h"
#include "DACombatSystem.h"
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
	void EnableCollision(FDAWeaponPayload NewPayload);

	void SetDAOwner(class ADACharacter* TheOwner);

	UFUNCTION()
	FORCEINLINE TSubclassOf<class UAnimInstance> GetAnimBP() const { return AnimationBPClass; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void TriggerEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY()
	FDAWeaponPayload Payload;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ADACharacter* DAOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<class UAnimInstance> AnimationBPClass;
};
