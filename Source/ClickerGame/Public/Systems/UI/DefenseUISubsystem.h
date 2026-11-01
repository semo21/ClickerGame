// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/MyWorldSubsystemBase.h"
#include "DefenseUISubsystem.generated.h"

class UDefenseUISettings;
/**
 * 
 */
UCLASS(Config=Game, DefaultConfig)
class CLICKERGAME_API UDefenseUISubsystem : public UMyWorldSubsystemBase
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

protected:
	virtual TSubclassOf<AGameModeBase> GetRequiredGameModeClass() const override;

private:
	UPROPERTY(Config)
	TSoftObjectPtr<UDefenseUISettings> UISettingsAsset;

	UPROPERTY()
	TObjectPtr<UDefenseUISettings> UISettings;
};
