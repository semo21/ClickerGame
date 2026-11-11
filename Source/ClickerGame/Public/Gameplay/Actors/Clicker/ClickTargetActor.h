// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ClickTargetActor.generated.h"

class UNiagaraSystem;
class USoundBase;

UCLASS(Abstract)
class CLICKERGAME_API AClickTargetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClickTargetActor();
	virtual void Tick(float DeltaTime) override;
	void HandleClicked(const FVector& HitLocation);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Feedback")
	TObjectPtr<UNiagaraSystem> ClickEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Feedback")
	TObjectPtr<USoundBase> ClickSound;
};
