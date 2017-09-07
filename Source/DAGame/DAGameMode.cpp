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
#include "DAWidget.h"
#include "LevelSequencePlayer.h"

ADAGameMode::ADAGameMode()
{
	if (!PlayerControllerClass)
		PlayerControllerClass = ADAPlayerController::StaticClass();
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

void ADAGameMode::CancelCurrent()
{
	if (MenuStack.Size() > 0) {
		MenuStack.Peek()->Cancel();
	}
}

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

void ADAGameMode::AddMenu(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (MenuStack.Size() > 0) {
		UDAWidget* DAW = MenuStack.Peek();
		if (DAW) {
			if (DAW->StaticClass() == NewWidgetClass->GetSuperClass()) {
				UE_LOG(LogTemp, Warning, TEXT("Already open"));
				return;
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
	}
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
		Old->OnClose();
		Old->RemoveFromViewport();
	}

	if (OpenPrevious && MenuStack.Size() > 0) {
		UDAWidget* DAW = MenuStack.Peek();
		if (DAW) {
			DAW->AddToViewport();
			DAW->OnOpen();
		}
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
	CloseCurrentMenu(false);
	MenuStack.Clear();
}


