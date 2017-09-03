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
#include "DAPlayerController.h"
#include "EngineUtils.h" 

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

	FStringAssetReference FOSequenceName("/Game/Sequences/FadeOut");
	FadeOutSequence = Cast<ULevelSequence>(FOSequenceName.TryLoad());

	FadeIn();
}

void ADAMainGameMode::FadeIn()
{
	if (FadeInSequence) {
		FMovieSceneSequencePlaybackSettings Settings;
		SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), FadeInSequence, Settings);
		if (SequencePlayer)
			SequencePlayer->Play();
	}
}

void ADAMainGameMode::FadeOut()
{
	if (FadeOutSequence) {
		FMovieSceneSequencePlaybackSettings Settings;
		SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), FadeOutSequence, Settings);
		if (SequencePlayer)
			SequencePlayer->Play();
	}
}

void ADAMainGameMode::TriggerRestEvent()
{
	FadeOut();
	GetWorldTimerManager().SetTimer(RestTimerHandle, this, &ADAMainGameMode::RestartLevel, 3.f, false);
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
		}
	}
}