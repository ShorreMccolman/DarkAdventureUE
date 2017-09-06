// Fill out your copyright notice in the Description page of Project Settings.

#include "DAMainGameMode.h"
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


ADAMainGameMode::ADAMainGameMode()
{
	if (!PlayerControllerClass)
		PlayerControllerClass = ADAPlayerController::StaticClass();
}

void ADAMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	ShowHUDWidget(true);

	FStringAssetReference FISequenceName("/Game/Sequences/FadeIn");
	FadeInSequence = Cast<ULevelSequence>(FISequenceName.TryLoad());
	if (FadeInSequence) {
		FMovieSceneSequencePlaybackSettings Settings;
		SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), FadeInSequence, Settings);
	}

	FadeIn();
}

void ADAMainGameMode::OpenStartMenu()
{
	AddMenu(StartMenuWidgetClass);
}

void ADAMainGameMode::OpenRestMenu()
{
	AddMenu(RestMenuWidgetClass);
	ResetLevel();
}

void ADAMainGameMode::AcceptCurrent()
{
	if (MenuStack.Size() > 0) {
		MenuStack.Peek()->Accept();
	}
}

void ADAMainGameMode::CancelCurrent()
{
	if (MenuStack.Size() > 0) {
		MenuStack.Peek()->Cancel();
	}
}

void ADAMainGameMode::NavigateCurrent(EDAInputDirection Direction)
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

void ADAMainGameMode::FadeIn()
{
	if (SequencePlayer) {
		SequencePlayer->SetPlayRate(1.f);
		SequencePlayer->Play();
	}
}

void ADAMainGameMode::FadeOut()
{
	if (SequencePlayer) {
		SequencePlayer->SetPlayRate(-1.f);
		SequencePlayer->Play();
	}
}

void ADAMainGameMode::TriggerRestEvent()
{
	FadeOut();
	GetWorldTimerManager().SetTimer(RestTimerHandle, this, &ADAMainGameMode::OpenRestMenu, 3.f, false);
}

void ADAMainGameMode::TriggerDeathEvent()
{
	FadeOut();
	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &ADAMainGameMode::RestartLevel, 3.f, false);
}

void ADAMainGameMode::ResetLevel()
{
	ADAPlayer* Player = Cast<ADAPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player) {
		Player->Reset();
	}

	for (TActorIterator<ADAEnemy> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		ADAEnemy* Enemy = *ActorItr;
		Enemy->Reset();
	}
}

void ADAMainGameMode::RestartLevel()
{
	GetWorldTimerManager().ClearTimer(DeathTimerHandle);
	GetWorldTimerManager().ClearTimer(RestTimerHandle);

	ResetLevel();

	FadeIn();
}

void ADAMainGameMode::ShowHUDWidget(bool ShouldShow)
{
	if (ShouldShow && CurrentHUDWidget == nullptr) {
		CurrentHUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentHUDWidget != nullptr) {
			CurrentHUDWidget->AddToViewport();
		}
	} else if (!ShouldShow && CurrentHUDWidget != nullptr) {
		CurrentHUDWidget->RemoveFromViewport();
		CurrentHUDWidget = nullptr;
	}
}

void ADAMainGameMode::ChangeMenu(TSubclassOf<UUserWidget> NewWidgetClass)
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

void ADAMainGameMode::AddMenu(TSubclassOf<UUserWidget> NewWidgetClass)
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

void ADAMainGameMode::HideCurrentMenu()
{
	if (MenuStack.Size() > 0) {
		UDAWidget* Old = MenuStack.Peek();
		Old->OnClose();
		Old->RemoveFromViewport();
	}
}

void ADAMainGameMode::CloseCurrentMenu(bool OpenPrevious)
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

void ADAMainGameMode::CloseAllMenus()
{
	CloseCurrentMenu(false);
	MenuStack.Clear();
}