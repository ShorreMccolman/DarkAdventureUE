// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DAPlayer.generated.h"

UCLASS()
class DAGAME_API ADAPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADAPlayer();

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

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetIsLocked() { return Locked; }

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

protected:
	// Called when the game starts or when spawned
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

	UPROPERTY(EditAnywhere)
	class ADAPlayer* TargetEnemy;
	
private:

	void StandardMotion(float DeltaTime);

	void LockedMotion(float DeltaTime);

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
};
