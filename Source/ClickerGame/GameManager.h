// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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


	UClickerUIManager* GetUIManager() const;
};
