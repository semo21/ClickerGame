// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Systems/MyWorldSubsystemBase.h"
#include "Gameplay/Types/DefenseTypes.h"

#include "DefenseEconomySubsystem.generated.h"

class UDefenseEconomySettings;
/**
 * 
 */
UCLASS(Config=Game, DefaultConfig)
class CLICKERGAME_API UDefenseEconomySubsystem : public UMyWorldSubsystemBase
{
	GENERATED_BODY()

	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	double CalculateSettlementReward(EDefenseMatchState Result) const;

protected:
	virtual TSubclassOf<AGameModeBase> GetRequiredGameModeClass() const override;

private:

	UPROPERTY(Config)
	TSoftObjectPtr<UDefenseEconomySettings> EconomySettingsAsset;
	UPROPERTY(Transient)
	TObjectPtr<UDefenseEconomySettings> EconomySettings;

};
