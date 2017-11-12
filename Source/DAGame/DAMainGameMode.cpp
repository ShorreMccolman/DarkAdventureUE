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
#include "UI/DAWidget.h"
#include "UI/DAHUDWidget.h"
#include "DARegion.h"
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
		CurrentHUDWidget->UpdateCharacterAndDisplay(PlayerCharacter);
	}
}

void ADAMainGameMode::ShowHUDWidget(bool ShouldShow)
{
	if (ShouldShow && CurrentHUDWidget == nullptr) {
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		CurrentHUDWidget = Cast<UDAHUDWidget>(Widget);
		if (CurrentHUDWidget) {
			CurrentHUDWidget->AddToViewport();
			if(CurrentRegion)
				CurrentHUDWidget->DisplayRegion(CurrentRegion->GetRegionName());
		}
	}
	else if (!ShouldShow && CurrentHUDWidget) {
		CurrentHUDWidget->RemoveFromViewport();
		CurrentHUDWidget = nullptr;
	}
}

void ADAMainGameMode::RefreshHUD()
{
	if (CurrentHUDWidget) {
		CurrentHUDWidget->DoDisplayUpdate();
	}
}

void ADAMainGameMode::RefreshHUD(int SoulsGained)
{
	if (CurrentHUDWidget) {
		CurrentHUDWidget->ShowEarnedSouls(SoulsGained);
		CurrentHUDWidget->DoDisplayUpdate();
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

	ResetLoadedRegions();
	ResetPlayer();

	AddMenu(RestMenuWidgetClass);
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

void ADAMainGameMode::SlayEnemy(FName RegionID, FString EnemyID)
{
	FDARegionData* Region = RegionData.FindByPredicate([RegionID](const FDARegionData& Data) {
		return Data.RegionID == RegionID;
	});
	if (Region) {
		Region->SlainEnemyIds.AddUnique(EnemyID);
	}
}

void ADAMainGameMode::CollectPickup(FName RegionID, FString PickupID)
{
	if (PickupID.IsEmpty())
		return;

	FDARegionData* Region = RegionData.FindByPredicate([RegionID](const FDARegionData& Data) {
		return Data.RegionID == RegionID;
	});
	if (Region) {
		Region->CollectedItemIds.AddUnique(PickupID);
	}
}

void ADAMainGameMode::RestartLevel()
{
	GetWorldTimerManager().ClearTimer(DeathTimerHandle);
	GetWorldTimerManager().ClearTimer(RestTimerHandle);

	ResetLoadedRegions();
	ResetPlayer();

	FadeIn();
}

void ADAMainGameMode::ResetPlayer()
{
	ADAPlayer* Player = Cast<ADAPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player) {
		Player->Reset();
	}
}

void ADAMainGameMode::SetRegionData(TArray<FDARegionData> Data) 
{ 
	RegionData = Data; 
}

FName ADAMainGameMode::GetRegionID() const
{
	if (!CurrentRegion) {
		return "";
	} else {
		return CurrentRegion->GetRegionID();
	}
}

void ADAMainGameMode::ResetLoadedRegions()
{
	for (auto &Region : RegionData) {
		Region.SlainEnemyIds.Empty();
	}

	for (auto Region : LoadedRegions) {
		InitRegionWithData(Region, true);
	}
}

void ADAMainGameMode::LoadRegion(FName RegionID, FLatentActionInfo LatentInfo)
{
	UGameplayStatics::LoadStreamLevel(this, RegionID, true, true, LatentInfo);
}

void ADAMainGameMode::UnloadRegion(FName RegionID, FLatentActionInfo LatentInfo)
{
	int index = LoadedRegions.IndexOfByPredicate([RegionID](ADARegion* const Region) {
		return Region->GetRegionID() == RegionID;
	});
	if (index != INDEX_NONE) {
		LoadedRegions[index]->UninitRegion();
		LoadedRegions.RemoveAt(index);
		UGameplayStatics::UnloadStreamLevel(this, RegionID, LatentInfo);
	}
}

void ADAMainGameMode::AddLoadedRegion(ADARegion* Region)
{
	if (Region)
	{
		LoadedRegions.AddUnique(Region);
		InitRegionWithData(Region, false);
	}
}

void ADAMainGameMode::InitRegionWithData(ADARegion* Region, bool ShouldRefresh)
{
	FName RegionID = Region->GetRegionID();
	int index = RegionData.IndexOfByPredicate([RegionID](const FDARegionData& Data) {
		return Data.RegionID == RegionID;
	});

	if (index != INDEX_NONE) {
		Region->InitRegion(RegionData[index]);
	}
	else {
		RegionData.Add(FDARegionData(RegionID));
		Region->InitRegion();
	}
}

void ADAMainGameMode::EnterRegion(ADARegion* Region)
{
	if (Region) 
	{
		CurrentRegion = Region;
		if (CurrentHUDWidget) 
		{
			CurrentHUDWidget->DisplayRegion(CurrentRegion->GetRegionName());
		}
	}
}

void ADAMainGameMode::LeaveRegion(ADARegion* Region)
{
	if (Region == CurrentRegion) {
		CurrentRegion = nullptr;
	}
}