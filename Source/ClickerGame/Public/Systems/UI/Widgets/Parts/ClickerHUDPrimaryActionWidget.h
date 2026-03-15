// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/UI/Widgets/Parts/ClickerHUDPartWidgetBase.h"
#include "GameplayTagContainer.h"

#include "ClickerHUDPrimaryActionWidget.generated.h"

class UClickerUISubsystem;
class AMyPlayerController;
class UButton;

UCLASS()
class CLICKERGAME_API UClickerHUDPrimaryActionWidget : public UClickerHUDPartWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void InitializePart_Implementation(UClickerUISubsystem* InUI, AMyPlayerController* InPC) override;

protected:
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	TObjectPtr<UButton> Btn_Upgrade;

	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly)
	TObjectPtr<UButton> Btn_Boost;

	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly)
	TObjectPtr<UButton> Btn_Test;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Action")
	FGameplayTag UpgradeActionTag;


};
