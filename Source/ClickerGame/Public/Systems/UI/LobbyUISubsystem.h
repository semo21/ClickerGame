// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/MyWorldSubsystemBase.h"
#include "LobbyUISubsystem.generated.h"

/**
 * 
 */
UCLASS()
class CLICKERGAME_API ULobbyUISubsystem : public UMyWorldSubsystemBase
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
protected:
	virtual TSubclassOf<AGameModeBase> GetRequiredGameModeClass() const override;	
};
