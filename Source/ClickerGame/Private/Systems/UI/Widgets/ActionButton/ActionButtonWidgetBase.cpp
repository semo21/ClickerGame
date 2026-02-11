// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"

#include "Systems/UI/Widgets/ActionButton/ActionButtonWidgetBase.h"
#include "Systems/UI/ClickerUISubsystem.h"

const FActionButtonDefinition* UActionButtonWidgetBase::GetDefinition() const {
	if (!ActionTag.IsValid())	return nullptr;

	const UWorld* World = GetWorld();
	if (!World)					return nullptr;

	UGameInstance* GI = World->GetGameInstance();
	if (!GI)					return nullptr;

	const UClickerUISubsystem* UISubsystem = GI->GetSubsystem<UClickerUISubsystem>();
	if (!UISubsystem)			return nullptr;

	return UISubsystem->FindActionButtonDefinition(ActionTag);
}

void UActionButtonWidgetBase::NativeOnInitialized() {
	Super::NativeOnInitialized();
	RefreshFromData();
	if (Btn_Root) {
		Btn_Root->OnClicked.AddDynamic(this, &UActionButtonWidgetBase::HandleClicked);
	}
}

void UActionButtonWidgetBase::NativePreConstruct() {
	Super::NativePreConstruct();
	RefreshFromData();
	if (IsDesignTime() && !DefaultStyle && !bOverrideLabel && !bOverrideIcon) {
		OverrideLabelText = PreviewLabelText;
		bOverrideLabel = true;

		OverrideIconTexture = nullptr;
		bOverrideIcon = bPreviewIcon;

		Mode = EActionButtonMode::Auto;
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

void UActionButtonWidgetBase::SetMode(EActionButtonMode InMode) {
	Mode = InMode;
	ApplyResolvedDataToWidgets();
}

void UActionButtonWidgetBase::HandleClicked() {
	OnClicked.Broadcast();
}

FText UActionButtonWidgetBase::ResolveLabel() const {
	if (bOverrideLabel) {
		return OverrideLabelText;
	}

	
	if (const FActionButtonDefinition* Def = GetDefinition()) {
		return Def->LabelText;
	}
	return FText::GetEmpty();
}

UTexture2D* UActionButtonWidgetBase::ResolveIcon() const {
	if (bOverrideIcon) {
		return OverrideIconTexture.Get();
	}

	if (const FActionButtonDefinition* Def = GetDefinition()) {
		return Def->IconTexture.Get();
	}
	return nullptr;
}

bool UActionButtonWidgetBase::ResolveEnabled() const {
	if (const FActionButtonDefinition* Def = GetDefinition()) {
		return Def->bDefaultEnabled;
	}
	return true;
}

EActionButtonMode UActionButtonWidgetBase::ResolveMode() const {
	if (const FActionButtonDefinition* Def = GetDefinition()) {
		return Def->Mode;
	}

	return EActionButtonMode::Auto;
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
	ApplyMode(ResolveMode());
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

void UActionButtonWidgetBase::RefreshFromData() {
	const FText Label = ResolveLabel();
	UTexture2D* Icon = ResolveIcon();
	const bool bEnabled = ResolveEnabled();
	const EActionButtonMode Mode = ResolveMode();

	SetLabelText(Label);
	SetIcon(Icon);
	SetEnabledState(bEnabled);

	SetMode(Mode);
}