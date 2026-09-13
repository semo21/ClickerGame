// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Player/MyPlayerControllerBase.h"

// public field
void AMyPlayerControllerBase::HandleActionButtonClicked(const FGameplayTag& ActionTag) {

}

// protected field
void AMyPlayerControllerBase::BeginPlay() {
	Super::BeginPlay();	
}

void AMyPlayerControllerBase::SetupInputComponent() {
	Super::SetupInputComponent();

	if (IsLocalController()) {
		bEnableClickEvents = true;
		bShowMouseCursor = true;

		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(InputMode);		
	}
}

