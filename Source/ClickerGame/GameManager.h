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
	virtual void Init() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	UAudioConfigDataAsset* AudioConfig;

	UPROPERTY()
	UClickerUIManager* UIManager;

	UClickerUIManager* GetUIManager() const;
};
