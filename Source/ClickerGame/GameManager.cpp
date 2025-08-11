// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "AudioConfigDataAsset.h"
#include "Kismet/GameplayStatics.h"

#include "ClickerUIManager.h"
#include "MyPlayerController.h"
#include "ClickerComponent.h"


void UGameManager::Init() {
	Super::Init();
}

void UGameManager::OnStart() {
	Super::OnStart();
	Initialize();
}

void UGameManager::Initialize() {
	if (bInitialized) return;
	bInitialized = true;

	UWorld* World = GetWorld();
	if (!ensureAlways(World)) return;
		
	PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!ensureAlwaysMsgf(PlayerController, TEXT("PlayerController is not ready"))) return;

	if (!UIManager) {
		UClass* ClassType = UIManagerClass ? *UIManagerClass : UClickerUIManager::StaticClass();		
		UIManager = NewObject<UClickerUIManager>(this, ClassType);
		ensureAlways(UIManager);
		if (UIManager) {
			UIManager->Initialize(this);
		}
	}

	if (!HUDWidget && HUDWidgetClass) {
		HUDWidget = CreateWidget<UUserWidget>(PlayerController, HUDWidgetClass);
		ensureAlways(HUDWidget);
		if (HUDWidget && !HUDWidget->IsInViewport()) {
			HUDWidget->AddToViewport();
		}
	}

	if (!ClickerComponent) {
		ClickerComponent = NewObject<UClickerComponent>(PlayerController);
		ensureAlways(ClickerComponent);
		if (ClickerComponent) {
			ClickerComponent->RegisterComponent();
			ClickerComponent->Initialize(this);
		}
	}
	//HUDWidget = CreateWidget<UUserWidget>(PlayerController, HUDWidgetClass);
	//ClickerComponent = NewObject<UClickerComponent>(PlayerController);
	//ensureAlways(ClickerComponent);
	//UIManager = NewObject<UClickerUIManager>(this, UIManagerClass);	

	//PlayerController->Initialize(this);
	//ClickerComponent->Initialize(this);
	//UIManager->Initialize(this);
}
