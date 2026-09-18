// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Systems/Economy/Data/MetaEconomySnapshot.h"
#include "InstancedStruct.h"

#include "PlayerSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CLICKERGAME_API UPlayerSaveGame : public USaveGame
{
	GENERATED_BODY()

public:	
	UPROPERTY(SaveGame) TMap<FName, FInstancedStruct> LevelSnapshots;
	UPROPERTY(SaveGame) FMetaEconomySnapshot MetaSnapshot;
};
