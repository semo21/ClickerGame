// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ClickerComponent.generated.h"

UCLASS()
class CLICKERGAME_API UClickerComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void HandleClick();
	void HandleUpgrade();

	float AccumulatedTime;
};