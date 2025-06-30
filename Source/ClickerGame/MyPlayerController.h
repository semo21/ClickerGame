// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
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

	// called when the button clicked
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

	void HideUpgradeSuccessText();


private:
	UPROPERTY()
	UClickerComponent* ClickerComponent;

	//UPROPERTY()
	//UUserWidget* ClickerUI;

	//UPROPERTY()
	//UTextBlock* CurrencyText;

	//UPROPERTY()
	//UTextBlock* ClickValueText;

	//UPROPERTY()
	//UTextBlock* UpgradeCostText;

	//UPROPERTY()
	//UTextBlock* PassiveIncomeText;

	//UPROPERTY()
	//UButton* UpgradeButton;

	UPROPERTY()
	UTextBlock* UpgradeSuccessText;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* FloatUpFade;

	//UPROPERTY()
	//TArray<UClickFloatingTextWidget*> FloatingTextPool;

	UPROPERTY()
	UClickerUIManager* UIManager;

	UFUNCTION()
	UClickFloatingTextWidget* GetFloatingTextWidgetFromPool();
	
	
	


	FTimerHandle UpgradeSuccessTimerHandle;

	void OnClick();
	void SpawnFloatingText(const FString& Text, const FVector2D& ScreenPosition);
};
