// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DACharacter.h"
#include "DAPlayer.generated.h"

UCLASS()
class DAGAME_API ADAPlayer : public ADACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADAPlayer();

	UFUNCTION()
	void InitPlayer();

	UFUNCTION(BlueprintCallable)
	void SavePlayer();

	UFUNCTION(BlueprintCallable)
	void AddItemsToInventory(FName ItemID, int Quantity);

	UFUNCTION(BlueprintCallable)
	void ChangeRestState(bool IsResting);

	UFUNCTION()
	void SnapshotOrigin();

	UFUNCTION()
	virtual void Reset() override;

	UFUNCTION()
	void TryInteract();

	UFUNCTION()
	void AddPotentialInteractable(AActor* Interactable);

	UFUNCTION()
	void RemovePotentialInteractable(AActor* Interactable);

	UFUNCTION()
	void SetCurrentInteractable(AActor* Interactable);

	FORCEINLINE AActor* GetCurrentInteractable() const { return CurrentInteractable; }

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UFUNCTION()
	void RotateCameraBoom(const float Magnitude);

	UFUNCTION()
	void ZoomCameraBoom(const float Magnitude);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void LoadPlayer();

	UPROPERTY()
	class ADAMainGameMode* GameMode;

	UPROPERTY(EditAnywhere)
	class APlayerStart* PlayerStart;

	UPROPERTY()
	class UDAPlayerSave* PlayerSave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* CurrentInteractable;

	UPROPERTY()
	TArray<AActor*> PotentialInteractables;

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
};
