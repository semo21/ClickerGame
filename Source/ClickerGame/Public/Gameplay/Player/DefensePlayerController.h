// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Player/MyPlayerControllerBase.h"
#include "Gameplay/Actors/Defense/DefenseGridManager.h"
#include "Gameplay/Types/DefenseTypes.h"

#include "DefensePlayerController.generated.h"

class ADefenseTowerBase;
/**
 * 
 */
UCLASS()
class CLICKERGAME_API ADefensePlayerController : public AMyPlayerControllerBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION() void OnClick();
	void HandleMatchEnded(EDefenseMatchState Result);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, Category="Defense")
	TSubclassOf<ADefenseTowerBase> TowerClass;

private:
	UPROPERTY()
	TObjectPtr<class ADefenseGridManager> GridRef;
};
