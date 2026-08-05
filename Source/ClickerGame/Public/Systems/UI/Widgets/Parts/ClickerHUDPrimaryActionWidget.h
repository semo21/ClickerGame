// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Systems/UI/Widgets/Parts/ClickerHUDPartWidgetBase.h"

#include "ClickerHUDPrimaryActionWidget.generated.h"

class UClickerUISubsystem;
class AMyPlayerController;
class UActionButtonWidgetBase;

UCLASS()
class CLICKERGAME_API UClickerHUDPrimaryActionWidget : public UClickerHUDPartWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void InitializePart_Implementation(UClickerUISubsystem* InUI, AMyPlayerController* InPC) override;

protected:
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	TObjectPtr<UActionButtonWidgetBase> Btn_Upgrade;

	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly)
	TObjectPtr<UActionButtonWidgetBase> Btn_Boost;

	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly)
	TObjectPtr<UActionButtonWidgetBase> Btn_Test;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Actions")
	FGameplayTag UpgradeActionTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Actions")
	FGameplayTag BoostActionTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Actions")
	FGameplayTag TestActionTag;
};
