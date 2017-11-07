// Fill out your copyright notice in the Description page of Project Settings.

#include "DAGameMode.h"
#include "DAPlayer.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "DACharacter.h"
#include "DAEnemy.h"
#include "EngineUtils.h" 
#include "UI/DAWidget.h"
#include "LevelSequencePlayer.h"
#include "DAItemManager.h"
#include "UI/DAConfirmPopup.h"

ADAGameMode::ADAGameMode()
{
	if (!PlayerControllerClass)
		PlayerControllerClass = ADAPlayerController::StaticClass();

	ItemManager = CreateDefaultSubobject<UDAItemManager>(TEXT("ItemManager"));
}

void ADAGameMode::BeginPlay()
{
	Super::BeginPlay();

	FStringAssetReference FISequenceName("/Game/Sequences/FadeIn");
	FadeInSequence = Cast<ULevelSequence>(FISequenceName.TryLoad());
	if (FadeInSequence) {
		FMovieSceneSequencePlaybackSettings Settings;
		SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), FadeInSequence, Settings);
	}

	FadeIn();
}

void ADAGameMode::AcceptCurrent()
{
	if (MenuStack.Size() > 0) {
		MenuStack.Peek()->Accept();
	}
}

void ADAGameMode::DeleteCurrent()
{
	if (MenuStack.Size() > 0) {
		MenuStack.Peek()->Delete();
	}
}

void ADAGameMode::CancelCurrent()
{
	if (MenuStack.Size() > 0) {
		MenuStack.Peek()->Cancel();
	}
}

void ADAGameMode::ToggleFace()
{
	if (MenuStack.Size() > 0) {
		MenuStack.Peek()->Switch();
	}
}

void ADAGameMode::RightButton()
{
	if (MenuStack.Size() > 0) {
		MenuStack.Peek()->RightButton();
	}
}

void ADAGameMode::LeftButton()
{
	if (MenuStack.Size() > 0) {
		MenuStack.Peek()->LeftButton();
	}
}

// Didnt want a default behaviour for start button so I'm leaving this empty but virtual
void ADAGameMode::StartButton()
{

}

void ADAGameMode::NavigateCurrent(EDAInputDirection Direction)
{
	if (MenuStack.Size() > 0) {
		UDAWidget* Menu = MenuStack.Peek();
		if (Menu) {
			switch (Direction)
			{
			case EDAInputDirection::DAInputDirection_Up:
				Menu->NavigateUp();
				break;
			case EDAInputDirection::DAInputDirection_Right:
				Menu->NavigateRight();
				break;
			case EDAInputDirection::DAInputDirection_Down:
				Menu->NavigateDown();
				break;
			case EDAInputDirection::DAInputDirection_Left:
				Menu->NavigateLeft();
				break;
			default:
				break;
			}

		}
	}
}

UDAItem* ADAGameMode::GetItemDataForID(FName ID) const
{
	return ItemManager->GetItemByID(ID);
}

void ADAGameMode::ShowLoadingScreen()
{
	LoadingWidget = CreateWidget<UUserWidget>(GetWorld(), LoadingWidgetClass);
	if (LoadingWidget) {
		LoadingWidget->AddToViewport();
	}
}

void ADAGameMode::FadeIn()
{
	if (SequencePlayer) {
		SequencePlayer->SetPlayRate(1.f);
		SequencePlayer->Play();
	}
}

void ADAGameMode::FadeOut()
{
	if (SequencePlayer) {
		SequencePlayer->SetPlayRate(-1.f);
		SequencePlayer->Play();
	}
}

void ADAGameMode::ChangeMenu(TSubclassOf<UUserWidget> NewWidgetClass)
{
	HideCurrentMenu();

	if (NewWidgetClass != nullptr) {
		UUserWidget* CurrentMenuWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentMenuWidget != nullptr) {
			UDAWidget* DAW = Cast<UDAWidget>(CurrentMenuWidget);
			if (DAW) {
				DAW->AddToViewport();
				DAW->OnOpen();
				MenuStack.Push(DAW);

				ADAPlayerController* Controller = Cast<ADAPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
				if (Controller) {
					Controller->SetDAControlMode(EDAControlMode::DAControlMode_PlayMenu);
				}
			}

		}
	}
}

UUserWidget* ADAGameMode::AddMenu(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (MenuStack.Size() > 0) {
		UDAWidget* DAW = MenuStack.Peek();
		if (DAW) {
			if (DAW->StaticClass() == NewWidgetClass->GetSuperClass()) {
				UE_LOG(LogTemp, Warning, TEXT("Already open"));
				return nullptr;
			}
		}
	}

	if (NewWidgetClass != nullptr) {
		UUserWidget* CurrentMenuWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentMenuWidget != nullptr) {
			UDAWidget* DAW = Cast<UDAWidget>(CurrentMenuWidget);
			if (DAW) {
				DAW->AddToViewport();
				DAW->OnOpen();
				MenuStack.Push(DAW);

				ADAPlayerController* Controller = Cast<ADAPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
				if (Controller) {
					Controller->SetDAControlMode(EDAControlMode::DAControlMode_PlayMenu);
				}
			}
		}
		return CurrentMenuWidget;
	}
	return nullptr;
}

UUserWidget* ADAGameMode::AddConfirmationPopup(TSubclassOf<UDAConfirmPopup> NewPopupClass, FText Message)
{
	UUserWidget* Popup = AddMenu(NewPopupClass);
	if (Popup) {
		UDAConfirmPopup* CP = Cast<UDAConfirmPopup>(Popup);
		if (CP) {
			CP->MainText->SetText(Message);
		}
	}

	return Popup;
}

UUserWidget* ADAGameMode::AddPopupMenu(TSubclassOf<UDAWidget> NewPopupClass)
{
	UUserWidget* Popup = AddMenu(NewPopupClass);
	return Popup;
}

void ADAGameMode::HideCurrentMenu()
{
	if (MenuStack.Size() > 0) {
		UDAWidget* Old = MenuStack.Peek();
		Old->OnClose();
		Old->RemoveFromViewport();
	}
}

void ADAGameMode::CloseCurrentMenu(bool OpenPrevious)
{
	if (MenuStack.Size() > 0) {
		UDAWidget* Old = MenuStack.Pop();
		if (Old->IsMenuOpen()) {
			Old->OnClose();
			Old->RemoveFromViewport();
		}
	}

	if (MenuStack.Size() > 0) {
		UDAWidget* DAW = MenuStack.Peek();
		if (DAW) {
			if (OpenPrevious) {
				DAW->AddToViewport();
				DAW->OnOpen();
			}
			else {
				DAW->Refocus();
			}
		}
	}

	if (MenuStack.Size() == 0) {
		ADAPlayerController* Controller = Cast<ADAPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (Controller) {
			Controller->SetDAControlMode(EDAControlMode::DAControlMode_Play);
		}
	}
}

void ADAGameMode::ClosePopup()
{
	if (MenuStack.Size() > 0) {
		UDAWidget* Old = MenuStack.Pop();
		Old->OnClose();
		Old->RemoveFromViewport();
	}

	if (MenuStack.Size() == 0) {
		ADAPlayerController* Controller = Cast<ADAPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (Controller) {
			Controller->SetDAControlMode(EDAControlMode::DAControlMode_Play);
		}
	}
}

void ADAGameMode::CloseAllMenus()
{
	while(MenuStack.Size() > 0) {
		CloseCurrentMenu(false);
	}
}


