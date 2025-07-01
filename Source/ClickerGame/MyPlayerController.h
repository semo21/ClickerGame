// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "ClickFloatingTextWidget.h"
#include "ClickerUIManager.h"
#include "NiagaraSystem.h"

#include "MyPlayerController.generated.h"

class UClickerComponent;
UCLASS()
class CLICKERGAME_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void OnUpgradeClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floating Text")
	TSubclassOf<UClickFloatingTextWidget> FloatingTextWidgetClass;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Click Effect")
	UNiagaraSystem* ClickEffectAsset;

	AMyPlayerController();
	void UpdateCurrencyUI();
	FString FormatCurrency(float Value) const;

	TSubclassOf<UUserWidget> HUDWidgetClass;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY()
	UClickerComponent* ClickerComponent;

	UPROPERTY()
	UClickerUIManager* UIManager;
		
	void OnClick();
};
