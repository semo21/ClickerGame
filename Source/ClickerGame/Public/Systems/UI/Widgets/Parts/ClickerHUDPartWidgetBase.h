// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Systems/Economy/ClickerEconomySubsystem.h"

#include "ClickerHUDPartWidgetBase.generated.h"

class UClickerUISubsystem;
class AMyPlayerControllerBase;
UCLASS(Abstract, Blueprintable)
class CLICKERGAME_API UClickerHUDPartWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="UI")
	void InitializePart(UClickerUISubsystem* InUI, AMyPlayerControllerBase* InPC);
	virtual void InitializePart_Implementation(UClickerUISubsystem* InUI, AMyPlayerControllerBase* InPC);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void OnEconomyChangedUI(const FEconomySnapshot& Snapshot);
	virtual void OnEconomyChangedUI_Implementation(const FEconomySnapshot& Snapshot);

protected:
	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<UClickerUISubsystem> UIRef;
	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<AMyPlayerControllerBase> PCRef;
};
