// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Systems/UI/Widgets/Parts/ClickerHUDPartWidgetBase.h"

#include "ClickerHUDDevButtonsWidget.generated.h"

class UActionButtonWidgetBase;
class UClickerUISubsystem;
class AMyPlayerControllerBase;
/**
 * 
 */
UCLASS()
class CLICKERGAME_API UClickerHUDDevButtonsWidget : public UClickerHUDPartWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void InitializePart_Implementation(UClickerUISubsystem* InUI, AMyPlayerControllerBase* InPC) override;

protected:
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	TObjectPtr<UActionButtonWidgetBase> Btn_Save;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	TObjectPtr<UActionButtonWidgetBase> Btn_Load;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Actions")
	FGameplayTag SaveActionTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Actions")
	FGameplayTag LoadActionTag;
};
