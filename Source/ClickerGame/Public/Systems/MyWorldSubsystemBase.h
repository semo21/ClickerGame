// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "MyWorldSubsystemBase.generated.h"

class AGameModeBase;
/**
 *
 */
UCLASS(Abstract)
class CLICKERGAME_API UMyWorldSubsystemBase : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

protected:
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;
	virtual TSubclassOf<AGameModeBase> GetRequiredGameModeClass() const { return nullptr; }
};