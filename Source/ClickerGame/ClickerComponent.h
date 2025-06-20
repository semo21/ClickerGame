// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyPlayerController.h"

#include "ClickerComponent.generated.h"

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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void HandleClick();
	void HandleUpgrade();
	float GetCurrency() const;
	float GetClickValue() const;
	float GetUpgradeCost() const;
	float GetCurrencyPerSecond() const;

		
private:
	int32 ClickCount;
	float Currency = 0.0f;
	float Multiplier;
	float CurrencyPerClick;
	float CurrencyPerSecond;
	float AccumulatedTime;
	float ClickValue = 1.0f;
	float UpgradeCost = 10.0f;

	UPROPERTY()
	AMyPlayerController* CachedMyPlayerController = nullptr;
};