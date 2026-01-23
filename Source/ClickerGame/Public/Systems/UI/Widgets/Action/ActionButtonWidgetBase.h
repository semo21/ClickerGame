// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Systems/UI/Settings/ActionButtonStyleData.h"

#include "ActionButtonWidgetBase.generated.h"

class UButton;
class UTextBlock;
class UImage;
class UTexture2D;
class UWidgetSwitcher;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionButtonClicked);

UCLASS()
class CLICKERGAME_API UActionButtonWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="ActionButton|Data", meta=(ExposeOnSpawn="true"))
	TObjectPtr<UActionButtonStyleData> StyleData = nullptr;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="ActionButton|Overrides", meta=(ExposeOnspawn="true"))
	bool bOverrideLabel = false;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "ActionButton|Overrides", meta = (ExposeOnspawn = "true"))
	FText OverrideLabelText;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "ActionButton|Overrides", meta = (ExposeOnspawn = "true"))
	bool bOverrideIcon = false;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "ActionButton|Overrides", meta = (ExposeOnspawn = "true"))
	TObjectPtr<UTexture2D> OverrideIconTexture = nullptr;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "ActionButton", meta = (ExposeOnspawn = "true"))
	EActionButtonMode Mode = EActionButtonMode::Auto;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "ActionButton", meta = (ExposeOnspawn = "true"))
	bool bEnabled = true;

	UFUNCTION(BlueprintCallable, Category = "ActionButton")
	void SetLabelText(const FText& InText);

	UFUNCTION(BlueprintCallable, Category = "ActionButton")
	void SetIcon(UTexture2D* InTexture);

	UFUNCTION(BlueprintCallable, Category = "ActionButton")
	void SetEnabledState(bool bInEnabled);

	UFUNCTION(BlueprintCallable, Category="ActionButton")
	void SetMode(EActionButtonMode InMode);

	UPROPERTY(BlueprintAssignable, Category = "ActionButton")
	FOnActionButtonClicked OnClicked;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void SynchronizeProperties() override;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_Root = nullptr;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UWidgetSwitcher> Switcher_Mode = nullptr;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UImage> Img_DisabledOverlay = nullptr;

	// Icon Only
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UImage> Img_Icon_Only = nullptr;

	// Text Only
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> Txt_Label_Only = nullptr;

	// Icon + Text	
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UImage> Img_Icon = nullptr;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> Txt_Label = nullptr;

	// Preview
	UPROPERTY(EditDefaultsOnly, Category="ActionButton|Priview")
	FText PreviewLabelText = FText::FromString(TEXT("Preview"));

	UPROPERTY(EditDefaultsOnly, Category = "ActionButton|Preview")
	bool bPreviewIcon = false;

private:
	UFUNCTION()
	void HandleClicked();

	void ApplyResolvedDataToWidgets();
	void ApplyMode(EActionButtonMode FinalMode);
	
	FText ResolveLabel() const;
	UTexture2D* ResolveIcon() const;
	bool ResolveEnabled() const;
	EActionButtonMode ResolveMode() const;
};
