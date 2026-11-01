// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Result/DefenseResultWidget.h"

#include "Components/TextBlock.h"

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