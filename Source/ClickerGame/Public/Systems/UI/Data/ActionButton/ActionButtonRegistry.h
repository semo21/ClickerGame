// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"

#include "Systems/UI/Data/ActionButton/ActionButtonDefinition.h"
#include "Systems/UI/Types/ActionButtonTypes.h"

#include "ActionButtonRegistry.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class CLICKERGAME_API UActionButtonRegistry : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag, FActionButtonDefinition> Definitions;

	const FActionButtonDefinition* Find(const FGameplayTag& Tag) const {
		return Definitions.Find(Tag);
	}
	
};
