// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DAMainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ADAMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ADAMainGameMode();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ChangeMenuWidget(TSubclassOf<class UUserWidget> NewWidgetClass);

	UFUNCTION(BlueprintCallable)
	void TriggerDeathEvent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<class UUserWidget> StartingWidgetClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;

	UPROPERTY()
	FTimerHandle DeathTimerHandle;

	UFUNCTION()
	void RestartLevel();
	
};
