// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAGameMode.h"
#include "DARegionData.h"
#include "DAMainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ADAMainGameMode : public ADAGameMode
{
	GENERATED_BODY()
	
public:
	ADAMainGameMode();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ShowHUDWidget(bool ShouldShow);

	UFUNCTION(BlueprintCallable)
	void SetupHUD(class ADACharacter* PlayerCharacter);

	UFUNCTION(BlueprintCallable)
	void RefreshHUD();

	void RefreshHUD(int SoulsGained);

	UFUNCTION()
	void OpenRestMenu();

	UFUNCTION()
	void LoadRegion(FName RegionID, FLatentActionInfo LatentInfo);

	UFUNCTION()
	void UnloadRegion(FName RegionID, FLatentActionInfo LatentInfo);

	UFUNCTION()
	void SetRegionData(TArray<FDARegionData> Data);

	UFUNCTION()
	FORCEINLINE TArray<FDARegionData> GetRegionData() const { return RegionData; }

	UFUNCTION(BlueprintCallable)
	void TriggerDeathEvent();

	UFUNCTION(BlueprintCallable)
	void TriggerRestEvent();

	void ResetPlayer();

	UFUNCTION(BlueprintCallable)
	void ResetLoadedRegions();

	UFUNCTION(BlueprintCallable)
	void QuitToMainMenu();

	UFUNCTION()
	virtual void StartButton() override;

	UFUNCTION(BlueprintPure)
	FName GetRegionID() const;

	void AddLoadedRegion(ADARegion* Region);

	UFUNCTION(BlueprintCallable)
	void EnterRegion(class ADARegion* Region);

	UFUNCTION(BlueprintCallable)
	void LeaveRegion(class ADARegion* Region);

	void SlayEnemy(FName RegionID, FString EnemyID);

	void CollectPickup(FName RegionID, FString PickupID);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<class UUserWidget> RestMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<class UUserWidget> StartMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	class UDAHUDWidget* CurrentHUDWidget;

	UPROPERTY()
	FTimerHandle RestTimerHandle;

	UPROPERTY()
	FTimerHandle DeathTimerHandle;

	void InitRegionWithData(class ADARegion* Region, bool ShouldRefresh);

	UFUNCTION()
	void RestartLevel();

	UPROPERTY()
	class ADARegion* CurrentRegion;

	UPROPERTY()
	TArray<class ADARegion*> LoadedRegions;

	UPROPERTY()
	TArray<FDARegionData> RegionData;
};
