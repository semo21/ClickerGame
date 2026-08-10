// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GlobalHUDRootWidgetBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CLICKERGAME_API UGlobalHUDRootWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly)
	TObjectPtr<UPanelWidget> ToastPanel;

	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly)
	TObjectPtr<UPanelWidget> FloatingTextPanel;

	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly)
	TObjectPtr<UPanelWidget> ModalLayer;

};
