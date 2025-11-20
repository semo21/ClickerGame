// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Player/MyPlayerController.h"

#include "Blueprint/WidgetTree.h"
#include "UObject/ConstructorHelpers.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Components/CanvasPanelSlot.h"

#include "Systems/Economy/ClickerEconomySubsystem.h"
#include "Systems/UI/ClickerUISubsystem.h"
#include "Gameplay/Actors/ClickTargetActor.h"

// protected field
void AMyPlayerController::BeginPlay() {
	Super::BeginPlay();	

	auto* Eco = GetGameInstance()->GetSubsystem<UClickerEconomySubsystem>();
	auto* UI = GetGameInstance()->GetSubsystem<UClickerUISubsystem>();

	Eco->StartWorld(GetWorld());
	UI->ShowHUD(GetWorld());
}

void AMyPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	if (IsLocalController()) {
		bEnableClickEvents = true;
		bShowMouseCursor = true;

		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(InputMode);

		InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &AMyPlayerController::OnClick);
	}
}

// private field
void AMyPlayerController::OnClick() {
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	if (!HitResult.bBlockingHit || !HitResult.GetActor() || !HitResult.GetActor()->IsA(AClickTargetActor::StaticClass())) return;

	if (auto* Eco = GetGameInstance()->GetSubsystem<UClickerEconomySubsystem>()) {
		Eco->OnClicked();
		if (auto* UI = GetGameInstance()->GetSubsystem<UClickerUISubsystem>()) {
			UI->ShowClickEffect(HitResult.Location);
			UI->ShowFloatingText(FString::Printf(TEXT("%f"), Eco->GetSnapshot().CurrencyPerClick), HitResult.Location);
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
		Eco->TriggerOfflineReward();
	}
}