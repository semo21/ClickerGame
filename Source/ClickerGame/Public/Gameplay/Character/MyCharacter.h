// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class APortal;

UCLASS()
class CLICKERGAME_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void SetCurrentPortal(APortal* NewPortal);

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void ClearCurrentPortal(APortal* PortalToClear);

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void TryInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Interaction")
	TObjectPtr<APortal> CurrentPortal;
};
