// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "Systems/Economy/Data/GlobalEconomySnapshot.h"

#include "GlobalEconomySubsystem.generated.h"

class USaveManagerSubsystem;
/**
 *
 */
UCLASS()
class CLICKERGAME_API UGlobalEconomySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void StartGame();
	UFUNCTION(BlueprintCallable, Category = "Economy|Meta")
	void AddGlobalCurrency(double Amount);

	const FGlobalEconomySnapshot& GetSnapshot() const { return GlobalEconomySnapshot; }

private:
	UPROPERTY()	
	FGlobalEconomySnapshot GlobalEconomySnapshot;
	UPROPERTY()	
	TObjectPtr<USaveManagerSubsystem> SaveManagerRef;
	bool bStarted = false;
};
