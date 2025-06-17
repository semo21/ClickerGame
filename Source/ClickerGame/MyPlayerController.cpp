// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Blueprint/WidgetTree.h"
#include "UObject/ConstructorHelpers.h"
#include "ClickTargetActor.h"
#include "ClickerComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Components/CanvasPanelSlot.h"

AMyPlayerController::AMyPlayerController() {
	bEnableClickEvents = true;	
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Game/Widgets/WBP_ClickerUI"));
	if (WidgetClass.Succeeded()) {
		WidgetClassRef = WidgetClass.Class;
	}
}

void AMyPlayerController::BeginPlay() {
	Super::BeginPlay();

	ClickerComponent = NewObject<UClickerComponent>(this);
	ClickerComponent->RegisterComponent();

	if (WidgetClassRef) {
		ClickerUI = CreateWidget<UUserWidget>(this, WidgetClassRef);
		if (ClickerUI) {
			ClickerUI->AddToViewport();

			// 이름으로 위젯 내부 요소 바인딩
			UWidget* FoundWidget = ClickerUI->GetWidgetFromName(TEXT("CurrencyText"));
			CurrencyText = Cast<UTextBlock>(FoundWidget);

			UWidget* ClickValueWidget = ClickerUI->GetWidgetFromName(TEXT("ClickValueText"));
			ClickValueText = Cast<UTextBlock>(ClickValueWidget);

			UWidget* UpgradeCostWidget = ClickerUI->GetWidgetFromName(TEXT("UpgradeCostText"));
			UpgradeCostText = Cast<UTextBlock>(UpgradeCostWidget);

			UWidget* PassiveIncomeWidget = ClickerUI->GetWidgetFromName(TEXT("PassiveIncomeText"));
			PassiveIncomeText = Cast<UTextBlock>(PassiveIncomeWidget);

			UWidget* UpgradeButtonWidget = ClickerUI->GetWidgetFromName(TEXT("UpgradeButton"));
			UpgradeButton = Cast<UButton>(UpgradeButtonWidget);

			UWidget* UpgradeSuccessWidget = ClickerUI->GetWidgetFromName(TEXT("UpgradeSuccessText"));
			UpgradeSuccessText = Cast<UTextBlock>(UpgradeSuccessWidget);

			// 디버깅 로그
			if (!CurrencyText) {
				UE_LOG(LogTemp, Warning, TEXT("CurrencyText not found in widget!"));
			}

			if (UpgradeButton) {
				UpgradeButton->OnClicked.AddDynamic(this, &AMyPlayerController::OnUpgradeClicked);
			}

			if (UpgradeSuccessText) {
				UpgradeSuccessText->SetVisibility(ESlateVisibility::Collapsed);
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("UpgradeSuccessText not found!"));
			}
		}
	}

	FInputModeGameAndUI InputMode;
	InputMode.SetWidgetToFocus(ClickerUI->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);
	bShowMouseCursor = true;
}

FString AMyPlayerController::FormatCurrency(float Value) const {
	if (Value >= 1e9f)
		return FString::Printf(TEXT("%.2fB"), Value / 1e9f);
	else if (Value >= 1e6f)
		return FString::Printf(TEXT("%.2fM"), Value / 1e6f);
	else if (Value >= 1e3f)
		return FString::Printf(TEXT("%.2fK"), Value / 1e3f);
	else
		return FString::Printf(TEXT("%.0f"), Value);
}

void AMyPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	//UE_LOG(LogTemp, Warning, TEXT("SetupInputComponent called!"));

	if (InputComponent)
	{
		InputComponent->BindAction("Click", IE_Pressed, this, &AMyPlayerController::OnClick);
	}
}

void AMyPlayerController::OnClick() {
	//UE_LOG(LogTemp, Warning, TEXT("OnClick called!"));
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	//UE_LOG(LogTemp, Warning, TEXT("HitResult.bBlockingHit: %s"), HitResult.bBlockingHit ? TEXT("true") : TEXT("false"));

	if (!HitResult.bBlockingHit)	return;

	AActor* HitActor = HitResult.GetActor();
	if (!IsValid(HitActor))	return;

	//UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name: %s"), *HitActor->GetName());
	//UE_LOG(LogTemp, Warning, TEXT("Hit Actor Class: %s"), *HitActor->GetClass()->GetName());

	if (!HitActor->IsA(AClickTargetActor::StaticClass())) {
		//UE_LOG(LogTemp, Warning, TEXT("Hit actor is not AClickTargetActor!"));
		return;
	}

	AClickTargetActor* ClickedActor = Cast<AClickTargetActor>(HitActor);
	if (!IsValid(ClickedActor)) {
		//UE_LOG(LogTemp, Warning, TEXT("Hit actor is not AClickTargetActor!"));
		return;
	}

	if (ClickerComponent) {
		ClickerComponent->HandleClick();
		UpdateCurrencyUI();
		DrawDebugSphere(GetWorld(), HitResult.Location, 16.0f, 12, FColor::Green, false, 1.0f);

		FVector2D ScreenPosition;
		ProjectWorldLocationToScreen(HitResult.Location, ScreenPosition);
		SpawnFloatingText(TEXT("+") + FormatCurrency(ClickerComponent->GetClickValue()), ScreenPosition);
	}
}

void AMyPlayerController::UpdateCurrencyUI() {
	if (ClickerComponent) {
		float Current = ClickerComponent->GetCurrency();
		float ClickValue = ClickerComponent->GetClickValue();
		float UpgradeCost = ClickerComponent->GetUpgradeCost();
		float PassiveIncome = ClickerComponent->GetCurrencyPerSecond();

		if (CurrencyText) {
			CurrencyText->SetText(FText::FromString(FormatCurrency(Current)));
		}
		if (ClickValueText) {
			ClickValueText->SetText(FText::FromString(FString::Printf(TEXT("Click Value: %.2f"), ClickValue)));
		}
		if (UpgradeCostText) {
			UpgradeCostText->SetText(FText::FromString(FString::Printf(TEXT("Upgrade Cost: %.2f"), UpgradeCost)));
		}
		if (PassiveIncomeText) {
			PassiveIncomeText->SetText(FText::FromString(FString::Printf(TEXT("Passive Income: %.2f / sec"), PassiveIncome)));
		}
	}
}

void AMyPlayerController::OnUpgradeClicked() {
	if (ClickerComponent) {
		ClickerComponent->HandleUpgrade();
		UpdateCurrencyUI();

		if (UpgradeSuccessText) {
			UpgradeSuccessText->SetVisibility(ESlateVisibility::Visible);

			GetWorldTimerManager().SetTimer(UpgradeSuccessTimerHandle, this, &AMyPlayerController::HideUpgradeSuccessText, 2.0f, false);
		}
	}
}

void AMyPlayerController::HideUpgradeSuccessText() {
	if (UpgradeSuccessText) {
		UpgradeSuccessText->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AMyPlayerController::SpawnFloatingText(const FString& Text, const FVector2D& ScreenPosition) {
	if (!FloatingTextClass)	return;

	UClickFloatingTextWidget* FloatingTextWidget = GetFloatingTextWidgetFromPool();
	if (!FloatingTextWidget) return;	

	FloatingTextWidget->AddToViewport();

	UTextBlock* TextBlock = Cast<UTextBlock>(FloatingTextWidget->GetWidgetFromName(TEXT("FloatingText")));

	if (TextBlock) {
		TextBlock->SetText(FText::FromString(Text));
	}
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(FloatingTextWidget->Slot);
	if (CanvasSlot) {
		CanvasSlot->SetPosition(ScreenPosition);
	}

	if (FloatingTextWidget->FloatUpFade) {
		FloatingTextWidget->PlayAnimation(FloatingTextWidget->FloatUpFade);
	}

	FTimerHandle TempHandle;
	GetWorldTimerManager().SetTimer(TempHandle, FTimerDelegate::CreateLambda([FloatingTextWidget]() {
		FloatingTextWidget->RemoveFromParent();
		}), 1.0f, false);
}

UClickFloatingTextWidget* AMyPlayerController::GetFloatingTextWidgetFromPool() {
	for (UClickFloatingTextWidget* Widget : FloatingTextPool) {
		if (!Widget->IsInViewport()) {
			return Widget;
		}
	}

	if (FloatingTextWidgetClass) {
		UClickFloatingTextWidget* NewWidget = CreateWidget<UClickFloatingTextWidget>(this, FloatingTextWidgetClass);
		return NewWidget;
	}
	return nullptr;
}