// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ClickerComponent.generated.h"

class AMyPlayerController;
class UClickerSaveGame;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLICKERGAME_API UClickerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClickerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void HandleClick();
	void HandleUpgrade();
	float GetCurrency() const;
	float GetCurrencyPerClick() const;
	float GetUpgradeCost() const;
	float GetCurrencyPerSecond() const;

	void SaveProgress();
	void LoadProgress();

		
private:
	int32 ClickCount;
	float Currency = 0.0f;
	float Multiplier;	
	float CurrencyPerSecond;
	float AccumulatedTime;
	float CurrencyPerClick = 1.0f;
	float UpgradeCostBase;
	int32 UpgradeLevel = 0;

	UPROPERTY()
	AMyPlayerController* CachedMyPlayerController = nullptr;

	UFUNCTION()
	void RecalculateStats();
};