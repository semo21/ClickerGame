// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "ClickerUIManager.h"
#include "AudioConfigDataAsset.h"

void UGameManager::Init() {
	Super::Init();

	UIManager = NewObject<UClickerUIManager>(this);

	if (UIManager && AudioConfig) {
		UIManager->Initialize(AudioConfig);
	}
}

UClickerUIManager* UGameManager::GetUIManager() const {
	if (!UIManager) {
		UE_LOG(LogTemp, Warning, TEXT("UIManager is not initialized!"));
	}
	return UIManager;
}