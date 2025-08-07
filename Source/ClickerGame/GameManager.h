// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AudioConfigDataAsset.h"
#include "ClickerUIManager.h"
#include "MyPlayerController.h"
#include "ClickFloatingTextWidget.h"
#include "ClickerComponent.h"
#include "IdleRewardTextWidget.h"
#include "NiagaraSystem.h"
#include "UserWidget.h"

#include "GameManager.generated.h"


class UAudioConfigDataAsset;
class UClickerUIManager;
/**
 * 
 */
UCLASS()
class CLICKERGAME_API UGameManager : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	void Initialize();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Configuration Data Asset")
	TSubclassOf<UAudioConfigDataAsset> AudioConfigDataAssetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Manager")
	TSubclassOf<UClickerUIManager> UIManagerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Controller")
	TSubclassOf<AMyPlayerController> PlayerControllerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floating Text Widget")
	TSubclassOf<UClickFloatingTextWidget> FloatingTextWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle Reward Text Widget")
	TSubclassOf<UIdleRewardTextWidget> IdleRewardTextWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Click Effect")
	TSubclassOf<UNiagaraSystem> ClickEffectAssetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clicker Component")
	TSubclassOf<UClickerComponent> ClickerComponentClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Widget")
	TSubclassOf<UUserWidget> HUDWidgetClass;


	UClickerUIManager* GetUIManager() const { return UIManager; }
	UAudioConfigDataAsset* GetAudioConfigDataAsset() const { return AudioConfigDataAsset; }
	AMyPlayerController* GetPlayerController() const { return PlayerController; }
	UClickerComponent* GetClickerComponent() const { return ClickerComponent; }
	UClickFloatingTextWidget* GetFloatingTextWidget() const { return FloatingTextWidget; }
	UIdleRewardTextWidget* GetIdleRewardTextWidget() const { return IdleRewardTextWidget; }
	UNiagaraSystem* GetClickEffectAsset() const { return ClickEffectAsset; }
	UUserWIdget* GetHUDWidget() const { return HUDWidget; }

private:
	UAudioConfigDataAsset* AudioConfigDataAsset;
	UClickerUIManager* UIManager;
	AMyPlayerController* PlayerController;
	UClickerComponent* ClickerComponent;
	UClickerFloatingTextWidget* FloatingTextWidget;
	UIdleRewardTextWidget* IdleRewardTextWidget;
	UNiagaraSystem* ClickEffectAsset;
	UUserWidget* HUDWidget;
};
