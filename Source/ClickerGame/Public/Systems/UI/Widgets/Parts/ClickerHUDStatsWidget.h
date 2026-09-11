// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/UI/Widgets/Parts/ClickerHUDPartWidgetBase.h"
#include "ClickerHUDStatsWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class CLICKERGAME_API UClickerHUDStatsWidget : public UClickerHUDPartWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void InitializePart_Implementation(UClickerUISubsystem* InUI, AMyPlayerControllerBase* InPC) override;

	virtual void OnEconomyChangedUI_Implementation(const FEconomySnapshot& Snapshot) override;

protected:
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	TObjectPtr<UTextBlock> Txt_Value_Currency;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	TObjectPtr<UTextBlock> Txt_Value_CPC;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	TObjectPtr<UTextBlock> Txt_Value_UpgradeCost;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	TObjectPtr<UTextBlock> Txt_Value_CPS;
};
