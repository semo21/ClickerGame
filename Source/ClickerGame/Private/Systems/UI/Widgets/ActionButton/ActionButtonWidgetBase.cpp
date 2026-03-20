// Fill out your copyright notice in the Description page of Project Settings.
#include "Systems/UI/Widgets/ActionButton/ActionButtonWidgetBase.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"

#include "Systems/UI/ClickerUISubsystem.h"

void UActionButtonWidgetBase::InitializeButton(UClickerUISubsystem* InUI, FGameplayTag InTag) {
	CachedUI = InUI;
	ActionTag = InTag;
	UE_LOG(LogTemp, Warning, TEXT("UActionButtonWidgetBase::InitializeButton - Initialized with tag: %s"), *ActionTag.ToString());
	SynchronizeProperties();
}

const FActionButtonDefinition* UActionButtonWidgetBase::GetDefinition() const {
	if (!ActionTag.IsValid())	return nullptr;

	if (CachedUI.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("UActionButtonWidgetBase::GetDefinition - CachedUI is valid, trying to find definition for tag: %s"), *ActionTag.ToString());
		return CachedUI->FindActionButtonDefinition(ActionTag);
	}

	return nullptr;

	//const UWorld* World = GetWorld();
	//if (!World) return nullptr;

	//const UGameInstance* GI = World->GetGameInstance();
	//if (!GI) return nullptr;

	//const UClickerUISubsystem* UISubsystem = GI->GetSubsystem<UClickerUISubsystem>();
	//return UISubsystem ? UISubsystem->FindActionButtonDefinition(ActionTag) : nullptr;
	
}

void UActionButtonWidgetBase::NativeOnInitialized() {
	Super::NativeOnInitialized();
	if (Btn_Root) {
		Btn_Root->OnClicked.AddDynamic(this, &UActionButtonWidgetBase::HandleClicked);
	}
}

void UActionButtonWidgetBase::NativePreConstruct() {
	Super::NativePreConstruct();
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
	UE_LOG(LogTemp, Warning, TEXT("UActionButtonWidgetBase::HandleClicked - Button with tag %s clicked"), *ActionTag.ToString());
	OnClicked.Broadcast();
}

FText UActionButtonWidgetBase::ResolveLabel() const {
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

UTexture2D* UActionButtonWidgetBase::ResolveIcon() const {
	if (bOverrideIcon && !OverrideIconTexture.IsNull()) {
		return OverrideIconTexture.Get();
	}

	if (const FActionButtonDefinition* Def = GetDefinition()) {
		if (!Def->IconTexture.IsNull()) {
			return Def->IconTexture.LoadSynchronous();
		}		
	}
	return nullptr;
}

bool UActionButtonWidgetBase::ResolveEnabled() const {
	if (!bEnabled)	return false;

	if (const FActionButtonDefinition* Def = GetDefinition())
		return Def->bDefaultEnabled;

	return true;
}

EActionButtonMode UActionButtonWidgetBase::ResolveMode() const {
	if (Mode != EActionButtonMode::Auto)	return Mode;

	if (const FActionButtonDefinition* Def = GetDefinition()) 
		return Def->Mode;
	

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