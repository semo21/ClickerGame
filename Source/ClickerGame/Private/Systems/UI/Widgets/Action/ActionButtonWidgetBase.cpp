// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Action/ActionButtonWidgetBase.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"

void UActionButtonWidgetBase::NativeOnInitialized() {
	Super::NativeOnInitialized();

	if (Btn_Root) {
		Btn_Root->OnClicked.AddDynamic(this, &UActionButtonWidgetBase::HandleClicked);
	}
}

void UActionButtonWidgetBase::NativePreConstruct() {
	Super::NativePreConstruct();

	if (IsDesignTime() && !StyleData && !bOverrideLabel && !bOverrideIcon) {
		OverrideLabelText = PreviewLabelText;
		bOverrideLabel = true;

		OverrideIconTexture = nullptr;
		bOverrideIcon = bPreviewIcon;

		Type = EActionButtonType::Auto;
		bEnabled = true;		
	}	

	ApplyResolvedDataToWidgets();
}

void UActionButtonWidgetBase::SynchronizeProperties() {
	Super::SynchronizeProperties();

	ApplyResolvedDataToWidgets();
}

void UActionButtonWidgetBase::SetLabelText(const FText& InText) {
	bOverrideLabel = true;
	OverrideLabelText = InText;

	ApplyResolvedDataToWidgets();
}

void UActionButtonWidgetBase::SetIcon(UTexture2D* InTexture) {
	bOverrideIcon = true;
	OverrideIconTexture = InTexture;

	ApplyResolvedDataToWidgets();	
}

void UActionButtonWidgetBase::SetEnabledState(bool bInEnabled) {
	bEnabled = bInEnabled;
	ApplyResolvedDataToWidgets();
}

void UActionButtonWidgetBase::SetMode(EActionButtonType InType) {
	Type = InType;
	ApplyResolvedDataToWidgets();
}

void UActionButtonWidgetBase::HandleClicked() {
	OnClicked.Broadcast();
}

FText UActionButtonWidgetBase::ResolveLabel() const {
	if (bOverrideLabel) {
		return OverrideLabelText;
	}

	if (StyleData) {
		return StyleData->LabelText;
	}
	return FText::GetEmpty();
}

UTexture2D* UActionButtonWidgetBase::ResolveIcon() const {
	if (bOverrideIcon) {
		return OverrideIconTexture.Get();
	}
	if (StyleData) {
		return StyleData->IconTexture.Get();
	}

	return nullptr;
}

bool UActionButtonWidgetBase::ResolveEnabled() const {
	return bEnabled;
}

EActionButtonType UActionButtonWidgetBase::ResolveType() const {
	// 인스턴스 Mode가 Auto가 아니라면 인스턴스 Mode값 사용
	if (Type != EActionButtonType::Auto) {
		return Type;
	}

	// DA가 Auto가 아니라면 DA값 사용
	if (StyleData && StyleData->Type!= EActionButtonType::Auto) {
		return StyleData->Type;
	}

	// Auto: Label/Icon 존재 여부에 따라 결정
	const bool bHasLabel = !ResolveLabel().IsEmpty();
	const bool bHasIcon = (ResolveIcon() != nullptr);
	
	if (bHasLabel && bHasIcon)	return EActionButtonMode::IconText;
	if (bHasIcon)				return EActionButtonMode::IconOnly;
	if (bHasLabel)				return EActionButtonMode::TextOnly;

	// 아무것도 없다면 TextOnly로 설정
	return EActionButtonMode::TextOnly;
}

void UActionButtonWidgetBase::ApplyResolvedDataToWidgets() {
	// 1) Enabled / Disabled overlay
	const bool bFinalEnabled = ResolveEnabled();

	if (Btn_Root) {
		Btn_Root->SetIsEnabled(bFinalEnabled);
	}

	if (Img_DisabledOverlay) {
		Img_DisabledOverlay->SetVisibility(bFinalEnabled ? ESlateVisibility::Collapsed : ESlateVisibility::HitTestInvisible);
	}

	// 2) Label/Icon 값 적용
	const FText FinalLabel = ResolveLabel();
	const UTexture2D* FinalIcon = ResolveIcon();

	if (Txt_Label) {
		Txt_Label->SetText(FinalLabel);
	}
	if (Txt_Label_Only) {
		Txt_Label_Only->SetText(FinalLabel);
	}

	if (Img_Icon) {
		Img_Icon->SetBrushFromTexture(const_cast<UTexture2D*>(FinalIcon), true);
		Img_Icon->SetVisibility(FinalIcon ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	}
	if (Img_Icon_Only) {
		Img_Icon_Only->SetBrushFromTexture(const_cast<UTexture2D*>(FinalIcon), true);
		Img_Icon_Only->SetVisibility(FinalIcon ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	}

	// 3) Mode 적용
	ApplyType(ResolveType());
}

void UActionButtonWidgetBase::ApplyMode(EActionButtonMode FinalMode) {
	if (!Switcher_Mode) return;

	int32 index = 0;
	switch (FinalMode) {
	case EActionButtonMode::IconOnly:	index = 0; break;
	case EActionButtonMode::TextOnly:	index = 1; break;
	case EActionButtonMode::IconText:	index = 2; break;
	case EActionButtonMode::Auto:		index = 2; break;
	default:							index = 2; break;
	}

	Switcher_Mode->SetActiveWidgetIndex(index);
}