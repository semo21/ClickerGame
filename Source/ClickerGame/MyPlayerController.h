// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "ClickerUIManager.h"
#include "NiagaraSystem.h"

#include "MyPlayerController.generated.h"

class UClickFloatingTextWidget;
class UIdleRewardTextWidget;
class UClickerComponent;
class UGameManager;
UCLASS()
class CLICKERGAME_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void Initialize(UGameManager* InGameManager);

	UFUNCTION()
	void OnUpgradeClicked();

	UFUNCTION()
	void OnSaveClicked();

	UFUNCTION()
	void OnLoadClicked();

	void UpdateCurrencyUI();
	FString FormatCurrency(float Value) const;

	TSubclassOf<UUserWidget> HUDWidgetClass;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UClickerUIManager* UIManager;
	UClickerComponent* ClickerComponent;
	UNiagaraSystem* ClickEffectAsset;
	UClickFloatingTextWidget* FloatingTextWidget;
	UIdleRewardTextWidget* IdleRewardTextWidget;

	AMyPlayerController();
	void OnClick();
};
