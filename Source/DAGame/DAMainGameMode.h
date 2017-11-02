// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAGameMode.h"
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

	UFUNCTION(BlueprintCallable)
	void TriggerDeathEvent();

	UFUNCTION(BlueprintCallable)
	void TriggerRestEvent();

	UFUNCTION(BlueprintCallable)
	void ResetLevel();

	UFUNCTION(BlueprintCallable)
	void QuitToMainMenu();

	UFUNCTION()
	virtual void StartButton() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<class UUserWidget> RestMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<class UUserWidget> StartMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	class UUserWidget* CurrentHUDWidget;

	UPROPERTY()
	FTimerHandle RestTimerHandle;

	UPROPERTY()
	FTimerHandle DeathTimerHandle;

	UFUNCTION()
	void RestartLevel();
	
};
