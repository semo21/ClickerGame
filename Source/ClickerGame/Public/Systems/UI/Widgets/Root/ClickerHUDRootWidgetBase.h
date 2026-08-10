// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/UI/Widgets/Root/GlobalHUDRootWidgetBase.h"
#include "Systems/Economy/ClickerEconomySubsystem.h"
#include "ClickerHUDRootWidgetBase.generated.h"

class UClickerUISubsystem;
class AMyPlayerController;
class UClickerHUDPartWidgetBase;

UCLASS(Abstract, Blueprintable)
class CLICKERGAME_API UClickerHUDRootWidgetBase : public UGlobalHUDRootWidgetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="UI")
	void InitializeHUDRoot(UClickerUISubsystem* InUI, AMyPlayerController* InPC);

protected:
	UPROPERTY(meta=(BindWidgetOptional), BlueprintReadOnly)
	TObjectPtr<UClickerHUDPartWidgetBase> Part_Stats;

	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly)
	TObjectPtr<UClickerHUDPartWidgetBase> Part_PrimaryActions;

	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly)
	TObjectPtr<UClickerHUDPartWidgetBase> Part_DevButtons;

private:
	UFUNCTION()
	void HandleEconomyChangedUI(const FEconomySnapshot& Snapshot);

protected:
	UPROPERTY()
	TObjectPtr<UClickerUISubsystem> UIRef;

	UPROPERTY()
	TObjectPtr<AMyPlayerController> PCRef;
};
