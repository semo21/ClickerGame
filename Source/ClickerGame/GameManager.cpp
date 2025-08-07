// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "ClickerUIManager.h"
#include "AudioConfigDataAsset.h"



void UGameManager::Init() {
	Super::Init();

	Initialize();
}

void UGameManager::Initialize() {
	ClickerComponent = NewObject<UClickerComponent>(this, ClickerComponentClass);
	UIManager = NewObject<UClickerUIManager>(this, UIManagerClass);

	PlayerController = NewObject<AMyPlayerController>(this, PlayerControllerClass);
	PlayerController->Initialize(this);

	HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
}
