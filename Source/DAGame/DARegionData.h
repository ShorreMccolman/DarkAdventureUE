#pragma once

#include "CoreMinimal.h"
#include "DARegionData.generated.h"

USTRUCT(BlueprintType)
struct FDARegionData
{
	GENERATED_BODY()

	UPROPERTY()
	FName RegionID;

	UPROPERTY()
	TArray<FString> SlainEnemyIds;

	UPROPERTY()
	TArray<FString> CollectedItemIds;


	FDARegionData()
	{
		RegionID = "";
	}

	FDARegionData(FName ID) : RegionID(ID)
	{
		
	}
};