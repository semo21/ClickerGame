// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Systems/Progress/Data/GlobalProgressSnapshot.h"

#include "GlobalProgressSubsystem.generated.h"

class USaveManagerSubsystem;

/**
 * 
 */
UCLASS()
class CLICKERGAME_API UGlobalProgressSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void StartGame();

	UFUNCTION(BlueprintCallable, Category="Progress")
	bool IsLevelUnlocked(const FGameplayTag& LevelTag) const;

	UFUNCTION(BlueprintCallable, Category="Progress")
	void UnlockLevel(const FGameplayTag& LevelTag);

	const FGlobalProgressSnapshot& GetSnapshot() const { return GlobalProgressSnapshot; }

private:
	UPROPERTY()
	FGlobalProgressSnapshot GlobalProgressSnapshot;
	UPROPERTY()
	TObjectPtr<USaveManagerSubsystem> SaveManagerRef;
	bool bStarted = false;
};
