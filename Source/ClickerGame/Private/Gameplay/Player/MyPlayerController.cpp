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

	auto* Eco = GetWorld()->GetSubsystem<UClickerEconomySubsystem>();
	//auto* UI = GetGameInstance()->GetSubsystem<UClickerUISubsystem>();

	Eco->StartWorld(GetWorld());
	//UI->ShowHUD(GetWorld());
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

	if (auto* Eco = GetWorld()->GetSubsystem<UClickerEconomySubsystem>()) {
		Eco->OnClicked();
		if (auto* UI = GetGameInstance()->GetSubsystem<UClickerUISubsystem>()) {
			UI->ShowClickEffect(HitResult.Location);
			UI->ShowFloatingText(FString::Printf(TEXT("%f"), Eco->GetSnapshot().CurrencyPerClick), HitResult.Location);
		}
	}
}

void AMyPlayerController::OnUpgradeClicked() {
	if (auto* Eco = GetWorld()->GetSubsystem<UClickerEconomySubsystem>()) {
		const bool bSuccess = Eco->TryUpgrade();
		if (bSuccess) {
			if (auto* UI = GetGameInstance()->GetSubsystem<UClickerUISubsystem>()) {
				UI->ShowUpgradeSuccessText();
			}
		}
	}
}

void AMyPlayerController::OnBoostClicked() {
	if (auto* UI = GetGameInstance()->GetSubsystem<UClickerUISubsystem>()) {
		UE_LOG(LogTemp, Warning, TEXT("Boost button clicked - this is a placeholder action"));
	}
}

void AMyPlayerController::OnTestClicked() {
	if (auto* UI = GetGameInstance()->GetSubsystem<UClickerUISubsystem>()) {
		UE_LOG(LogTemp, Warning, TEXT("Test button clicked - this is a placeholder action"));
	}
}

void AMyPlayerController::OnSaveClicked() {
	if (auto* Eco = GetWorld()->GetSubsystem<UClickerEconomySubsystem>()) {
		Eco->RequestSave();
		UE_LOG(LogTemp, Warning, TEXT("Save button clicked - this is a placeholder action"));
	}
}

void AMyPlayerController::OnLoadClicked() {
	if (auto* Eco = GetWorld()->GetSubsystem<UClickerEconomySubsystem>()) {
		Eco->RequestLoad();
		UE_LOG(LogTemp, Warning, TEXT("Load button clicked - this is a placeholder action"));
	}
}

void AMyPlayerController::HandleActionButtonClicked(const FGameplayTag& ActionTag) {
	if (ActionTag.MatchesTagExact(FGameplayTag::RequestGameplayTag("UI.Action.Upgrade"))) {
		OnUpgradeClicked();
	}
	else if(ActionTag.MatchesTagExact(FGameplayTag::RequestGameplayTag("UI.Action.Boost"))) {
		OnBoostClicked();
	}
	else if(ActionTag.MatchesTagExact(FGameplayTag::RequestGameplayTag("UI.Action.Test"))) {
		OnTestClicked();
	}else if(ActionTag.MatchesTagExact(FGameplayTag::RequestGameplayTag("UI.Action.Save"))) {
		OnSaveClicked();
	}
	else if (ActionTag.MatchesTagExact(FGameplayTag::RequestGameplayTag("UI.Action.Load"))) {
		OnLoadClicked();
	}
}