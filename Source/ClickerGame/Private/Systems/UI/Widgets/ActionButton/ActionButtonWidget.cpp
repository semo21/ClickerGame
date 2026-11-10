// Fill out your copyright notice in the Description page of Project Settings.
#include "Systems/UI/Widgets/ActionButton/ActionButtonWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"

#include "Systems/UI/ClickerUISubsystem.h"
#include "Gameplay/Player/MyPlayerControllerBase.h"

void UActionButtonWidget::InitializeButton(AMyPlayerControllerBase* InPC, UClickerUISubsystem* InUI, FGameplayTag InTag) {
	CachedPC = InPC;
	CachedUI = InUI;
	ActionTag = InTag;
	SynchronizeProperties();
}

const FActionButtonDefinition* UActionButtonWidget::GetDefinition() const {
	if (!ActionTag.IsValid())	return nullptr;

	if (CachedUI.IsValid()) {
		return CachedUI->FindActionButtonDefinition(ActionTag);
	}

	return nullptr;
}

void UActionButtonWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();
	if (Btn_Root) {
		Btn_Root->OnClicked.AddDynamic(this, &UActionButtonWidget::HandleClicked);
	}
}

void UActionButtonWidget::NativePreConstruct() {
	Super::NativePreConstruct();

	ApplyResolvedDataToWidgets();
}

void UActionButtonWidget::SynchronizeProperties() {
	Super::SynchronizeProperties();

	ApplyResolvedDataToWidgets();
}

void UActionButtonWidget::SetLabelText(const FText& InText) {
	bOverrideLabel = true;
	OverrideLabelText = InText;

	ApplyResolvedDataToWidgets();
}

void UActionButtonWidget::SetIcon(UTexture2D* InTexture) {
	bOverrideIcon = true;
	OverrideIconTexture = InTexture;

	ApplyResolvedDataToWidgets();
}

void UActionButtonWidget::SetEnabledState(bool bInEnabled) {
	bOverrideEnabledValue = bInEnabled;
	ApplyResolvedDataToWidgets();
}

void UActionButtonWidget::SetMode(EActionButtonMode InMode) {
	Mode = InMode;
	ApplyResolvedDataToWidgets();
}

void UActionButtonWidget::HandleClicked() {
	if (!CachedPC.IsValid() || !CachedUI.IsValid() || !ActionTag.IsValid()) {
		return;
	}

	CachedPC->HandleActionButtonClicked(ActionTag);
	OnClicked.Broadcast();
}

FText UActionButtonWidget::ResolveLabel() const {
	if (bOverrideLabel && !OverrideLabelText.IsEmpty()) {
		return OverrideLabelText;
	}


	if (const FActionButtonDefinition* Def = GetDefinition()) {
		if (!Def->LabelText.IsEmpty()) {
			return Def->LabelText;
		}		
	}
	return FText::GetEmpty();
}

UTexture2D* UActionButtonWidget::ResolveIcon() const {
	if (bOverrideIcon && !OverrideIconTexture.IsNull()) {
		return OverrideIconTexture.LoadSynchronous();
	}

	if (const FActionButtonDefinition* Def = GetDefinition()) {
		if (!Def->IconTexture.IsNull()) {
			return Def->IconTexture.LoadSynchronous();
		}		
	}
	return nullptr;
}

bool UActionButtonWidget::ResolveEnabled() const {
	if (bOverrideEnabled) {
		return bOverrideEnabledValue;
	}

	if (const FActionButtonDefinition* Def = GetDefinition())
		return Def->bDefaultEnabled;

	return true;
}

EActionButtonMode UActionButtonWidget::ResolveMode() const {
	if (Mode != EActionButtonMode::Auto)	return Mode;

	if (const FActionButtonDefinition* Def = GetDefinition()) 
		return Def->Mode;
	

	return EActionButtonMode::Auto;
}

void UActionButtonWidget::ApplyResolvedDataToWidgets() {
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
	ApplyMode(ResolveMode());
}

void UActionButtonWidget::ApplyMode(EActionButtonMode FinalMode) {
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