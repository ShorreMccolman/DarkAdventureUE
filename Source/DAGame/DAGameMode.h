// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DAPlayerController.h"
#include "DAWidget.h"
#include "DAGameMode.generated.h"

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
class ADAGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ADAGameMode();

	UFUNCTION()
	void AcceptCurrent();

	UFUNCTION()
	void DeleteCurrent();

	UFUNCTION()
	void CancelCurrent();

	UFUNCTION()
	void ToggleFace();

	UFUNCTION()
	void RightButton();

	UFUNCTION()
	void LeftButton();

	UFUNCTION()
	virtual void StartButton();

	void NavigateCurrent(EDAInputDirection Direction);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ChangeMenu(TSubclassOf<class UUserWidget> NewWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	class UUserWidget* AddMenu(TSubclassOf<class UUserWidget> NewWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	class UUserWidget* AddConfirmationPopup(TSubclassOf<class UDAConfirmPopup> NewPopupClass, FText Message);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	class UUserWidget* AddPopupMenu(TSubclassOf<class UDAWidget> NewPopupClass);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void HideCurrentMenu();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void CloseCurrentMenu(bool OpenPrevious);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void CloseAllMenus();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ClosePopup();

	UFUNCTION(BlueprintCallable)
	void FadeIn();

	UFUNCTION(BlueprintCallable)
	void FadeOut();

	UFUNCTION()
	FORCEINLINE class UDAItemManager* GetItemManager() const { return ItemManager; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDAItemManager* ItemManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	FDAStack MenuStack;

	UPROPERTY()
	class ULevelSequence* FadeInSequence;

	UPROPERTY()
	class ULevelSequencePlayer* SequencePlayer;
};
