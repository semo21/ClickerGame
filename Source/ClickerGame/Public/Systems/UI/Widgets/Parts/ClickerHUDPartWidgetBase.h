// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Systems/Economy/ClickerEconomySubsystem.h"

#include "ClickerHUDPartWidgetBase.generated.h"

class UClickerUISubsystem;
class UClickerEconomySubsystem;
class AMyPlayerController;
UCLASS(Abstract, Blueprintable)
class CLICKERGAME_API UClickerHUDPartWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="UI")
	void InitializePart(UClickerUISubsystem* UI, UClickerEconomySubsystem* Economy, AMyPlayerController* PC);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void OnEconomyChanged(const FEconomySnapshot& Snapshot);
};
