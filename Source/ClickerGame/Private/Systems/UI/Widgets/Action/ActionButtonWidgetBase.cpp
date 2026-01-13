// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Action/ActionButtonWidgetBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UActionButtonWidgetBase::NativeOnInitialized() {
	Super::NativeOnInitialized();

	if (Btn_Root) {
		Btn_Root->OnClicked.AddDynamic(this, &UActionButtonWidgetBase::HandleClicked);
	}
}

void UActionButtonWidgetBase::NativePreConstruct() {
	Super::NativePreConstruct();
}

void UActionButtonWidgetBase::SetLabelText(const FText& InText) {
	if (Txt_Label) Txt_Label->SetText(InText);
}

void UActionButtonWidgetBase::SetIcon(UTexture2D* InTexture) {
	if (!Img_Icon) return;

	Img_Icon->SetVisibility(InTexture ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
	Img_Icon->SetBrushFromTexture(InTexture, true);
}

void UActionButtonWidgetBase::SetEnabledState(bool bEnabled) {
	if (Btn_Root) Btn_Root->SetIsEnabled(bEnabled);

	if (Img_DisabledOverlay) {
		Img_DisabledOverlay->SetVisibility(bEnabled ? ESlateVisibility::Collapsed : ESlateVisibility::SelfHitTestInvisible);
	}
}

void UActionButtonWidgetBase::HandleClicked() {
	OnClicked.Broadcast();
}
