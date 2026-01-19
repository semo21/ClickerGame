// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActionButtonWidgetBase.generated.h"

class UButton;
class UTextBlock;
class UTexture2D;
class UWidgetSwitcher;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionButtonClicked);

UENUM(BlueprintType)
enum class EActionButtonMode : uint8 {
	IconOnly,
	TextOnly,
	IconText
};

UCLASS()
class CLICKERGAME_API UActionButtonWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "ActionButton")
	void SetLabelText(const FText& InText);

	UFUNCTION(BlueprintCallable, Category = "ActionButton")
	void SetIcon(UTexture2D* InTexture);

	UFUNCTION(BlueprintCallable, Category = "ActionButton")
	void SetEnabledState(bool bInEnabled);

	UPROPERTY(BlueprintAssignable, Category = "ActionButton")
	FOnActionButtonClicked OnClicked;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Root = nullptr;

	UPROPERTY(meta = (BindWidgetOptional))
	UWidgetSwitcher* Switcher_Mode = nullptr;

	UPROPERTY(meta = (BindWidgetOptional))
	UImage* Img_DisabledOverlay = nullptr;

	// Icon Only
	UPROPERTY(meta = (BindWidgetOptional))
	UTexture2D* Img_Icon_Only = nullptr;

	// Text Only
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* Txt_Label_Only = nullptr;

	// Icon + Text	
	UPROPERTY(meta = (BindWidgetOptional))
	UTexture2D* Img_Icon = nullptr;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* Txt_Label = nullptr;

	// Preview
	UPROPERTY(EditDefaultsOnly, Category="ActionButton|Priview")
	FText PreviewLabelText = FText::FromString(TEXT("Preview"));

	UPROPERTY(EditDefaultsOnly, Category = "ActionButton|Preview")
	bool bPreviewIcon = false;

private:
	UFUNCTION()
	void HandleClicked();
};
