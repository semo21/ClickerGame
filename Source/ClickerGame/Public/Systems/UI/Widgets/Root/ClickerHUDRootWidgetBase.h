// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Systems/Economy/ClickerEconomySubsystem.h"
#include "ClickerHUDRootWidgetBase.generated.h"

class UClickerUISubsystem;
class UClickerEconomySubsystem;
class AMyPlayerController;
class UClickerHUDPartWidgetBase;

UCLASS(Abstract, Blueprintable)
class CLICKERGAME_API UClickerHUDRootWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="UI")
	void InitializeRoot(UClickerUISubsystem* InUI, UClickerEconomySubsystem* InEconomy, AMyPlayerController* InPC);

protected:
	UPROPERTY(meta=(BindWidgetOptional), BlueprintReadOnly)
	TObjectPtr<UClickerHUDPartWidgetBase> StatsPart;

	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly)
	TObjectPtr<UClickerHUDPartWidgetBase> PrimaryActionPart;

	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly)
	TObjectPtr<UClickerHUDPartWidgetBase> DevButtonsPart;

private:
	UFUNCTION()
	void HandleEconomyChangedUI(const FEconomySnapshot& Snapshot);

	UPROPERTY()
	TObjectPtr<UClickerUISubsystem> UIRef;

	UPROPERTY()
	TObjectPtr<UClickerEconomySubsystem> EcoRef;

	UPROPERTY()
	TObjectPtr<AMyPlayerController> PCRef;
};
