// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "Blueprint/WidgetTree.h"
#include "UObject/ConstructorHelpers.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Components/CanvasPanelSlot.h"

#include "ClickerEconomySubsystem.h"
#include "ClickerUISubsystem.h"
#include "ClickTargetActor.h"
#include "ClickerComponent.h"

void AMyPlayerController::BeginPlay() {
	Super::BeginPlay();

	bEnableClickEvents = true;
	bShowMouseCursor = true;
	FInputModeGameAndUI InputMode; 
	//InputMode.SetWidgetToFocus(InGameManager->GetHUDWidget()->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);

	if (auto* Eco = GetGameInstance()->GetSubsystem<UClickerEconomySubsystem>())
		Eco->StartWorld(GetWorld());

	if (auto* UI = GetGameInstance()->GetSubsystem<UClickerUISubsystem>())
		UI->ShowHUD(GetWorld());
}

void AMyPlayerController::OnClick() {
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	if (!HitResult.bBlockingHit || !HitResult.GetActor() || !HitResult.GetActor()->IsA(AClickTargetActor::StaticClass())) return;
		
	if (auto* Eco = GetGameInstance()->GetSubsystem<UClickerEconomySubsystem>()) {
		Eco->OnClicked();
		if (auto* UI = GetGameInstance()->GetSubsystem<UClickerUISubsystem>()) {
			UI->ShowClickEffect(HitResult.Location);
			UI->ShowFloatingText(TEXT("%d", Eco->MakeSnapshot().CurrencyPerClick), HitResult.Location);
		}
	}
}

void AMyPlayerController::OnUpgradeClicked() {
	if (auto* Eco = GetGameInstance()->GetSubsystem<UClickerEconomySubsystem>()) {
		const bool bSuccess = Eco->TryUpgrade();
		if (bSuccess) {
			if (auto* UI = GetGameInstance()->GetSubsystem<UClickerUISubsystem>()) {
				UI->ShowUpgradeSuccessText();
			}
		}
	}
}

void AMyPlayerController::OnSaveClicked() {
	if (auto* Eco = GetGameInstance()->GetSubsystem<UClickerEconomySubsystem>()) {
		Eco->RequestSave();
	}
}

void AMyPlayerController::OnLoadClicked() {
	if (auto* Eco = GetGameInstance()->GetSubsystem<UClickerEconomySubsystem>()) {
		Eco->RequestLoad();
	}
}