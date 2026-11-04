// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Result/DefenseResultWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UDefenseResultWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();
	if (Btn_Lobby) {
		Btn_Lobby->OnClicked.AddDynamic(this, &UDefenseResultWidget::HandleLobbyButtonClicked);
	}
}

void UDefenseResultWidget::HandleLobbyButtonClicked() {
	UGameplayStatics::OpenLevel(this, LobbyLevelName);
}

void UDefenseResultWidget::SetResult(EDefenseMatchState Result) {
	if (!Txt_Result) return;

	switch (Result) {
	case EDefenseMatchState::Victory:
		Txt_Result->SetText(FText::FromString(TEXT("Victory")));
		break;
	case EDefenseMatchState::Defeat:
		Txt_Result->SetText(FText::FromString(TEXT("Defeat")));
		break;
	default:
		break;
	}
}