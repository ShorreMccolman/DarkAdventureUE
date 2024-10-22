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

	UFUNCTION(BlueprintCallable)
	void SavePlayer();

	UFUNCTION(BlueprintCallable)
	void AddItemsToInventory(FName ItemID, int Quantity);

	UFUNCTION(BlueprintCallable)
	void ChangeRestState(bool IsResting);

	void SnapshotOrigin();

	virtual void Reset() override;

	void InitPlayer();

	void TryInteract();

	void AddPotentialInteractable(AActor* Interactable);

	void RemovePotentialInteractable(AActor* Interactable);

	void SetCurrentInteractable(AActor* Interactable);

	FORCEINLINE AActor* GetCurrentInteractable() const { return CurrentInteractable; }

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

protected:
	UPROPERTY(EditAnywhere, Category = Temp)
	class APlayerStart* PlayerStart;

	UPROPERTY()
	class ADAMainGameMode* GameMode;

	UPROPERTY()
	class UDAPlayerSave* PlayerSave;

	UPROPERTY()
	AActor* CurrentInteractable;

	UPROPERTY()
	TArray<AActor*> PotentialInteractables;

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void LoadPlayer();
};
