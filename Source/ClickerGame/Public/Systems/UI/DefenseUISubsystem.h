// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Gameplay/Types/DefenseTypes.h"
#include "Systems/MyWorldSubsystemBase.h"
#include "DefenseUISubsystem.generated.h"

class UDefenseUISettings;
class UDefenseResultWidget;
class AMyPlayerController;
/**
 * 
 */
UCLASS(Config=Game, DefaultConfig)
class CLICKERGAME_API UDefenseUISubsystem : public UMyWorldSubsystemBase
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void ShowResult(APlayerController* PC, EDefenseMatchState Result);

protected:
	virtual TSubclassOf<AGameModeBase> GetRequiredGameModeClass() const override;

private:
	UPROPERTY(Config)
	TSoftObjectPtr<UDefenseUISettings> UISettingsAsset;

	UPROPERTY()
	TObjectPtr<UDefenseUISettings> UISettings;

	UPROPERTY()
	TObjectPtr<UDefenseResultWidget> ResultWidget;
};
