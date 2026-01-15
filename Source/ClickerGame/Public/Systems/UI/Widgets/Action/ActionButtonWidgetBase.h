// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActionButtonWidgetBase.generated.h"

class UButton;
class UTextBlock;
class UImage;
class UTexture2D;
class UOverlay;
class UHorizontalBox;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionButtonClicked);

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
	UOverlay* Overlay_Content = nullptr;

	UPROPERTY(meta = (BindWidgetOptional))
	UHorizontalBox* HBox_Content = nullptr;

	UPROPERTY(meta = (BindWidgetOptional))
	UImage* Img_Icon = nullptr;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* Txt_Label = nullptr;

	UPROPERTY(meta = (BindWidgetOptional))
	UImage* Img_DisabledOverlay = nullptr;	

	UPROPERTY(EditDefaultsOnly, Category="ActionButton|Priview")
	FText PreviewLabelText = FText::FromString(TEXT("Preview"));

	UPROPERTY(EditDefaultsOnly, Category = "ActionButton|Preview")
	bool bPreviewIcon = false;

private:
	void HandleClicked();
};
