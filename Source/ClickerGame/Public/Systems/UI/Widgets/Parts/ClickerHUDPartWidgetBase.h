// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Systems/Economy/ClickerEconomySubsystem.h"

#include "ClickerHUDPartWidgetBase.generated.h"

class UClickerUISubsystem;
class AMyPlayerController;
UCLASS(Abstract, Blueprintable)
class CLICKERGAME_API UClickerHUDPartWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="UI")
	void InitializePart(UClickerUISubsystem* InUI, AMyPlayerController* InPC);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void OnEconomyChangedUI(const FEconomySnapshot& Snapshot);

protected:
	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<UClickerUISubsystem> UIRef;
	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<AMyPlayerController> PCRef;
};
