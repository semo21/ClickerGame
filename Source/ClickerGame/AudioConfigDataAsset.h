// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Sound/SoundBase.h"

#include "AudioConfigDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class CLICKERGAME_API UAudioConfigDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RewardSound")
	USoundBase* RewardSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ClickSound")
	USoundBase* ClickSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UpgradeSound")
	USoundBase* UpgradeSound;

	UFUNCTION()
	USoundBase* GetRewardSound() const { return RewardSound; }

	UFUNCTION()
	USoundBase* GetUpgradeSound() const { return UpgradeSound; }

	UFUNCTION()
	USoundBase* GetClickSound() const { return ClickSound; }

private:

};
