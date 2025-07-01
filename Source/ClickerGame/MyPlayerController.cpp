// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Blueprint/WidgetTree.h"
#include "UObject/ConstructorHelpers.h"
#include "ClickTargetActor.h"

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Components/CanvasPanelSlot.h"

AMyPlayerController::AMyPlayerController() {
	bEnableClickEvents = true;	
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Game/Widgets/WBP_ClickerUI"));
	if (WidgetClass.Succeeded()) {
		HUDWidgetClass = WidgetClass.Class;
	}
}

void AMyPlayerController::BeginPlay() {
	Super::BeginPlay();

	UIManager = NewObject<UClickerUIManager>(this);
	UIManager->Initialize(this);
	UIManager->ShowHUD();

	ClickerComponent = NewObject<UClickerComponent>(this);
	ClickerComponent->RegisterComponent();

	UIManager->SetClickerComponent(ClickerComponent);
	//UE_LOG(LogTemp, Warning, TEXT("Begin Play"));
	
	//UE_LOG(LogTemp, Warning, TEXT("UIManager: %s"), *GetNameSafe(UIManager));
	if (UIManager && UIManager->GetHUDWidget()) {
		//UE_LOG(LogTemp, Warning, TEXT("UIManager: HUDWidget is valid"));
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(UIManager->GetHUDWidget()->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(InputMode);
		bShowMouseCursor = true;
	}
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

	if (InputComponent)
	{
		InputComponent->BindAction("Click", IE_Pressed, this, &AMyPlayerController::OnClick);
	}
}

void AMyPlayerController::OnClick() {
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	if (!HitResult.bBlockingHit)	return;

	AActor* HitActor = HitResult.GetActor();
	if (!IsValid(HitActor))	return;

	if (!HitActor->IsA(AClickTargetActor::StaticClass())) {
		return;
	}

	AClickTargetActor* ClickedActor = Cast<AClickTargetActor>(HitActor);
	if (!IsValid(ClickedActor)) {
		return;
	}

	if (ClickerComponent) {
		ClickerComponent->HandleClick();
		UpdateCurrencyUI();

		UIManager->ShowClickEffect(HitResult.Location);
		UIManager->ShowFloatingText(TEXT("+") + FormatCurrency(ClickerComponent->GetClickValue()), HitResult.Location);

	}
}

void AMyPlayerController::UpdateCurrencyUI() {
	UIManager->UpdateScore();
}

void AMyPlayerController::OnUpgradeClicked() {
	if (ClickerComponent) {
		ClickerComponent->HandleUpgrade();
		UpdateCurrencyUI();

		if (UIManager) {
			UIManager->ShowUpgradeSuccessText();
		}
	}
}
