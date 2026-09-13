// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Player/ClickerPlayerController.h"

#include "Systems/Economy/ClickerEconomySubsystem.h"
#include "Systems/UI/ClickerUISubsystem.h"
#include "Gameplay/Actors/ClickTargetActor.h"

// private field
void AClickerPlayerController::OnClick() {
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	if (!HitResult.bBlockingHit || !HitResult.GetActor() || !HitResult.GetActor()->IsA(AClickTargetActor::StaticClass())) return;

	if (auto* Eco = GetWorld()->GetSubsystem<UClickerEconomySubsystem>()) {
		Eco->OnClicked();
		if (auto* UI = GetWorld()->GetSubsystem<UClickerUISubsystem>()) {
			UI->ShowClickEffect(HitResult.Location);
			UI->ShowFloatingText(FString::Printf(TEXT("%f"), Eco->GetSnapshot().CurrencyPerClick), HitResult.Location);
		}
	}
}

void AClickerPlayerController::OnUpgradeClicked() {
	if (auto* Eco = GetWorld()->GetSubsystem<UClickerEconomySubsystem>()) {
		const bool bSuccess = Eco->TryUpgrade();
		if (bSuccess) {
			if (auto* UI = GetWorld()->GetSubsystem<UClickerUISubsystem>()) {
				UI->ShowUpgradeSuccessText();
			}
		}
	}
}

void AClickerPlayerController::OnBoostClicked() {
	if (auto* UI = GetWorld()->GetSubsystem<UClickerUISubsystem>()) {
		UE_LOG(LogTemp, Warning, TEXT("Boost button clicked - this is a placeholder action"));
	}
}

void AClickerPlayerController::OnTestClicked() {
	if (auto* UI = GetWorld()->GetSubsystem<UClickerUISubsystem>()) {
		UE_LOG(LogTemp, Warning, TEXT("Test button clicked - this is a placeholder action"));
	}
}

void AClickerPlayerController::OnSaveClicked() {
	if (auto* Eco = GetWorld()->GetSubsystem<UClickerEconomySubsystem>()) {
		Eco->RequestSave();
		UE_LOG(LogTemp, Warning, TEXT("Save button clicked - this is a placeholder action"));
	}
}

void AClickerPlayerController::OnLoadClicked() {
	if (auto* Eco = GetWorld()->GetSubsystem<UClickerEconomySubsystem>()) {
		Eco->RequestLoad();
		UE_LOG(LogTemp, Warning, TEXT("Load button clicked - this is a placeholder action"));
	}
}

void AClickerPlayerController::HandleActionButtonClicked(const FGameplayTag& ActionTag) {
	if (ActionTag.MatchesTagExact(FGameplayTag::RequestGameplayTag("UI.Action.Upgrade"))) {
		OnUpgradeClicked();
	}
	else if (ActionTag.MatchesTagExact(FGameplayTag::RequestGameplayTag("UI.Action.Boost"))) {
		OnBoostClicked();
	}
	else if (ActionTag.MatchesTagExact(FGameplayTag::RequestGameplayTag("UI.Action.Test"))) {
		OnTestClicked();
	}
	else if (ActionTag.MatchesTagExact(FGameplayTag::RequestGameplayTag("UI.Action.Save"))) {
		OnSaveClicked();
	}
	else if (ActionTag.MatchesTagExact(FGameplayTag::RequestGameplayTag("UI.Action.Load"))) {
		OnLoadClicked();
	}
}

void AClickerPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	if (IsLocalController()) {
		InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &AClickerPlayerController::OnClick);
	}
}

