// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Gameplay/Types/DefenseTypes.h"

#include "DefenseResultWidget.generated.h"

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class CLICKERGAME_API UDefenseResultWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetResult(EDefenseMatchState Result);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Txt_Result;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_Lobby;
	
};
