// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "GlobalUISubsystem.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS()
class CLICKERGAME_API UGlobalUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void ShowRootUI(TSubclassOf<UUserWidget> RootWidgetClass);
	
	UFUNCTION(BlueprintCallable)
	void ClearRootUI();

	TObjectPtr<UUserWidget> GetCurrentRootWidget() const { return CurrentRootWidget; }

private:
	UPROPERTY()
	TObjectPtr<UUserWidget> CurrentRootWidget = nullptr;

	
	

	

};
