// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/MyWorldSubsystemBase.h"
#include "DefenseUISubsystem.generated.h"

/**
 * 
 */
UCLASS()
class CLICKERGAME_API UDefenseUISubsystem : public UMyWorldSubsystemBase
{
	GENERATED_BODY()
	
public:

protected:
	virtual TSubclassOf<AGameModeBase> GetRequiredGameModeClass() const override;
};
