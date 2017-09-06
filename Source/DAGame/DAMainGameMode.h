// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DAPlayerController.h"
#include "DAWidget.h"
#include "DAMainGameMode.generated.h"

USTRUCT()
struct FDAStack
{
	GENERATED_BODY()

	FDAStack()
	{

	}

	const int Size()
	{
		return Stack.Num();
	}

	void Push(UDAWidget* Widget)
	{
		Stack.Add(Widget);
	}

	UDAWidget* Pop()
	{
		if (Stack.Num() < 0)
			return nullptr;

		return Stack.Pop(true);
	}

	UDAWidget* Peek()
	{
		return Stack.Last();
	}

	void Clear()
	{
		Stack.Empty();
	}


private:
	UPROPERTY()
	TArray<UDAWidget*> Stack;
};

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
	void ShowHUDWidget(bool ShouldShow);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ChangeMenu(TSubclassOf<class UUserWidget> NewWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void AddMenu(TSubclassOf<class UUserWidget> NewWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void HideCurrentMenu();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void CloseCurrentMenu(bool OpenPrevious);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void CloseAllMenus();

	UFUNCTION(BlueprintCallable)
	void FadeIn();

	UFUNCTION(BlueprintCallable)
	void FadeOut();

	UFUNCTION(BlueprintCallable)
	void TriggerDeathEvent();

	UFUNCTION(BlueprintCallable)
	void TriggerRestEvent();

	UFUNCTION()
	void OpenRestMenu();

	UFUNCTION()
	void OpenStartMenu();

	UFUNCTION(BlueprintCallable)
	void ResetLevel();

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	FDAStack MenuStack;

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
