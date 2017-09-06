// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DAPlayerController.h"
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

	UFUNCTION()
	void AcceptCurrent();

	UFUNCTION()
	void CancelCurrent();

	void NavigateCurrent(EDAInputDirection Direction);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ChangeMenuWidget(TSubclassOf<class UUserWidget> NewWidgetClass);

	UFUNCTION()
	void FadeIn();

	UFUNCTION()
	void FadeOut();

	UFUNCTION(BlueprintCallable)
	void TriggerDeathEvent();

	UFUNCTION(BlueprintCallable)
	void TriggerRestEvent();

	UFUNCTION()
	void OpenMenu();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<class UUserWidget> StartingWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<class UUserWidget> MenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	class UUserWidget* CurrentWidget;

	UPROPERTY()
	class ULevelSequence* FadeInSequence;

	UPROPERTY()
	class ULevelSequencePlayer* SequencePlayer;

	UPROPERTY()
	FTimerHandle RestTimerHandle;

	UPROPERTY()
	FTimerHandle DeathTimerHandle;

	UFUNCTION()
	void RestartLevel();
	
};
