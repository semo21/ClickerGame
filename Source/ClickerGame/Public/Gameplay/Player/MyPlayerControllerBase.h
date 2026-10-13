// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"

#include "MyPlayerControllerBase.generated.h"

class UClickFloatingTextWidget;
class UIdleRewardTextWidget;

UCLASS()
class CLICKERGAME_API AMyPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()	
public:
	UFUNCTION()	virtual void HandleActionButtonClicked(const FGameplayTag& ActionTag);
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
};
