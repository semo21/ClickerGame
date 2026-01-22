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

	if (IsDesignTime()) {
		SetLabelText(PreviewLabelText);
		SetEnabledState(false);
	}	
}

void UActionButtonWidgetBase::SetLabelText(const FText& InText) {
	if (Txt_Label) Txt_Label->SetText(InText);
}

void UActionButtonWidgetBase::SetIcon(UTexture2D* InTexture) {
	if (!Img_Icon) return;

	
}

void UActionButtonWidgetBase::SetEnabledState(bool bInEnabled) {
	if (Btn_Root) Btn_Root->SetIsEnabled(bInEnabled);

	if (Img_DisabledOverlay) {
		
	}
}

void UActionButtonWidgetBase::HandleClicked() {
	OnClicked.Broadcast();
}
