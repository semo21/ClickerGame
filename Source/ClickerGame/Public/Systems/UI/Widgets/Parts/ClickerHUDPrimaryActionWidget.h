// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Systems/UI/Widgets/Parts/ClickerHUDPartWidgetBase.h"

#include "ClickerHUDPrimaryActionWidget.generated.h"

class UClickerUISubsystem;
class AClickerPlayerController;
class UActionButtonWidget;

UCLASS(Abstract)
class CLICKERGAME_API UClickerHUDPrimaryActionWidget : public UClickerHUDPartWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void InitializePart_Implementation(UClickerUISubsystem* InUI, AClickerPlayerController* InPC) override;

protected:
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	TObjectPtr<UActionButtonWidget> Btn_Upgrade;

	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly)
	TObjectPtr<UActionButtonWidget> Btn_Boost;

	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly)
	TObjectPtr<UActionButtonWidget> Btn_Test;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Actions")
	FGameplayTag UpgradeActionTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Actions")
	FGameplayTag BoostActionTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Actions")
	FGameplayTag TestActionTag;
};
