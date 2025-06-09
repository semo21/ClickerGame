// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Blueprint/WidgetTree.h"
#include "UObject/ConstructorHelpers.h"
#include "ClickTargetActor.h"
#include "ClickerComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

AMyPlayerController::AMyPlayerController() {
	bEnableClickEvents = true;	
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Game/Widgets/WBP_ClickerUI.WBP_ClickerUI_C"));
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

			// 디버깅 로그
			if (!CurrencyText) {
				UE_LOG(LogTemp, Warning, TEXT("CurrencyText not found in widget!"));
			}

			UWidget* UpgradeButtonWidget = ClickerUI->GetWidgetFromName(TEXT("UpgradeButton"));
			UpgradeButton = Cast<UButton>(UpgradeButtonWidget);

			if (UpgradeButton) {
				UpgradeButton->OnClicked.AddDynamic(this, &AMyPlayerController::OnUpgradeClicked);
			}
		}
	}

	FInputModeGameAndUI InputMode;
	InputMode.SetWidgetToFocus(ClickerUI->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);
	bShowMouseCursor = true;
}

void AMyPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	UE_LOG(LogTemp, Warning, TEXT("SetupInputComponent called!"));

	if (InputComponent)
	{
		InputComponent->BindAction("Click", IE_Pressed, this, &AMyPlayerController::OnClick);
	}
}

void AMyPlayerController::OnClick() {
	UE_LOG(LogTemp, Warning, TEXT("OnClick called!"));
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	UE_LOG(LogTemp, Warning, TEXT("HitResult.bBlockingHit: %s"), HitResult.bBlockingHit ? TEXT("true") : TEXT("false"));

	if (!HitResult.bBlockingHit)	return;

	AActor* HitActor = HitResult.GetActor();
	if (!IsValid(HitActor))	return;

	UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name: %s"), *HitActor->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Hit Actor Class: %s"), *HitActor->GetClass()->GetName());

	if (!HitActor->IsA(AClickTargetActor::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("Hit actor is not AClickTargetActor!"));
		return;
	}

	AClickTargetActor* ClickedActor = Cast<AClickTargetActor>(HitActor);
	if (!IsValid(ClickedActor)) {
		UE_LOG(LogTemp, Warning, TEXT("Hit actor is not AClickTargetActor!"));
		return;
	}

	if (ClickerComponent) {
		ClickerComponent->HandleClick();
		UpdateCurrencyUI();
		DrawDebugSphere(GetWorld(), HitResult.Location, 16.0f, 12, FColor::Green, false, 1.0f);
	}
}

void AMyPlayerController::UpdateCurrencyUI() {
	if (CurrencyText && ClickerComponent) {
		float Current = ClickerComponent->GetCurrency();
		CurrencyText->SetText(FText::FromString(FString::Printf(TEXT("Currency: %.2f\nUpgrade Cost: %.2f"), ClickerComponent->GetCurrency(), ClickerComponent->GetUpgradeCost())));
	}
}

void AMyPlayerController::OnUpgradeClicked() {
	if (ClickerComponent) {
		ClickerComponent->HandleUpgrade();
		UpdateCurrencyUI();
	}
}
