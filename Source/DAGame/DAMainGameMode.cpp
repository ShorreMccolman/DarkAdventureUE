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
#include "DAHUDWidget.h"
#include "LevelSequencePlayer.h"


ADAMainGameMode::ADAMainGameMode()
{

}

void ADAMainGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ADAMainGameMode::SetupHUD(ADACharacter* PlayerCharacter)
{
	ShowHUDWidget(true);
	if (CurrentHUDWidget != nullptr) {
		UDAHUDWidget* HUD = Cast<UDAHUDWidget>(CurrentHUDWidget);
		if (HUD) {
			HUD->UpdateCharacterAndDisplay(PlayerCharacter);
		}
	}
}

void ADAMainGameMode::ShowHUDWidget(bool ShouldShow)
{
	if (ShouldShow && CurrentHUDWidget == nullptr) {
		CurrentHUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentHUDWidget != nullptr) {
			CurrentHUDWidget->AddToViewport();
		}
	}
	else if (!ShouldShow && CurrentHUDWidget != nullptr) {
		CurrentHUDWidget->RemoveFromViewport();
		CurrentHUDWidget = nullptr;
	}
}

void ADAMainGameMode::RefreshHUD()
{
	if (CurrentHUDWidget != nullptr) {
		UDAHUDWidget* HUD = Cast<UDAHUDWidget>(CurrentHUDWidget);
		if (HUD) {
			HUD->DoDisplayUpdate();
		}
	}
}

void ADAMainGameMode::RefreshHUD(int SoulsGained)
{
	if (CurrentHUDWidget != nullptr) {
		UDAHUDWidget* HUD = Cast<UDAHUDWidget>(CurrentHUDWidget);
		if (HUD) {
			HUD->ShowEarnedSouls(SoulsGained);
			HUD->DoDisplayUpdate();
		}
	}
}

void ADAMainGameMode::QuitToMainMenu()
{
	ADAPlayer* Player = Cast<ADAPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player) {
		Player->SavePlayer();
	}
	ShowLoadingScreen();
	UGameplayStatics::OpenLevel(this,"Menu");
}

void ADAMainGameMode::StartButton()
{
	ADAPlayer* Player = Cast<ADAPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player) {
		Player->SavePlayer();
	}
	AddMenu(StartMenuWidgetClass);
}

void ADAMainGameMode::OpenRestMenu()
{
	if (SequencePlayer) {
		SequencePlayer->Pause();
	}
	AddMenu(RestMenuWidgetClass);
	ResetLevel();
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