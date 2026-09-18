// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "Systems/Economy/Data/MetaEconomySnapshot.h"

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

	void StartGame();

	UFUNCTION(BlueprintCallable, Category="Economy|Meta")
	bool IsLevelUnlocked(const FGameplayTag& LevelTag) const;

	UFUNCTION(BlueprintCallable, Category = "Economy|Meta")
	void UnlockLevel(const FGameplayTag& LevelTag);

	UFUNCTION(BlueprintCallable, Category = "Economy|Meta")
	void AddGlobalCurrency(double Amount);

	const FMetaEconomySnapshot& GetSnapshot() const { return MetaSnapshot; }

private:
	UPROPERTY()
	FMetaEconomySnapshot MetaSnapshot;

	UPROPERTY()
	TObjectPtr<USaveManagerSubsystem> SaveManagerRef;
	bool bStarted = false;
};
