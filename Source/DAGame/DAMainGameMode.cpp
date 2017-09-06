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

	ChangeMenuWidget(StartingWidgetClass);

	FStringAssetReference FISequenceName("/Game/Sequences/FadeIn");
	FadeInSequence = Cast<ULevelSequence>(FISequenceName.TryLoad());
	if (FadeInSequence) {
		FMovieSceneSequencePlaybackSettings Settings;
		SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), FadeInSequence, Settings);
	}

	FadeIn();
}

void ADAMainGameMode::OpenMenu()
{
	ChangeMenuWidget(MenuWidgetClass);

	ADAPlayerController* Controller = Cast<ADAPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (Controller) {
		Controller->SetDAControlMode(EDAControlMode::DAControlMode_PlayMenu);
	}
}

void ADAMainGameMode::AcceptCurrent()
{
	UDAWidget* Menu = Cast<UDAWidget>(CurrentWidget);
	if (Menu) {
		Menu->Accept();
	}
}

void ADAMainGameMode::CancelCurrent()
{

}

void ADAMainGameMode::NavigateCurrent(EDAInputDirection Direction)
{
	UDAWidget* Menu = Cast<UDAWidget>(CurrentWidget);
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
	GetWorldTimerManager().SetTimer(RestTimerHandle, this, &ADAMainGameMode::OpenMenu, 3.f, false);
}

void ADAMainGameMode::TriggerDeathEvent()
{
	FadeOut();
	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &ADAMainGameMode::RestartLevel, 3.f, false);
}

void ADAMainGameMode::RestartLevel()
{
	GetWorldTimerManager().ClearTimer(DeathTimerHandle);
	GetWorldTimerManager().ClearTimer(RestTimerHandle);

	ADAPlayer* Player = Cast<ADAPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player) {
		Player->Reset();
	}

	for (TActorIterator<ADAEnemy> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		ADAEnemy* Enemy = *ActorItr;
		Enemy->Reset();
	}

	FadeIn();
}

void ADAMainGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr) {
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr) {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
			UDAWidget* DAW = Cast<UDAWidget>(CurrentWidget);
			if (DAW) {
				DAW->OnOpen();
			}

		}
	}
}