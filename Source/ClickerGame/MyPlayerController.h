// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "NiagaraSystem.h"

#include "MyPlayerController.generated.h"

class UClickFloatingTextWidget;
class UIdleRewardTextWidget;

UCLASS()
class CLICKERGAME_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()	
public:
	UFUNCTION()	void OnClick();
	UFUNCTION()	void OnUpgradeClicked();
	UFUNCTION()	void OnSaveClicked();
	UFUNCTION()	void OnLoadClicked();
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
};
