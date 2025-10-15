// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/ClickerUISubsystem.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "Engine/GameViewportClient.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "TimerManager.h"

#include "Gameplay/Player/MyPlayerController.h"
#include "Systems/Economy/ClickerEconomySubsystem.h"
#include "Systems/UI/Widgets/Toast/ClickFloatingTextWidget.h"
#include "Systems/UI/Widgets/Toast/IdleRewardTextWidget.h"
#include "Systems/UI/Settings/ClickerUISettings.h"

// public field
void UClickerUISubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
	Collection.InitializeDependency(UClickerEconomySubsystem::StaticClass());

	EconomySubsystemRef = GetGameInstance()->GetSubsystem<UClickerEconomySubsystem>();
	checkf(EconomySubsystemRef, TEXT("UClickerUISubsystem::Initialize EconomySubsystemRef is null"));

	EconomySubsystemRef->OnEconomyChanged.AddUniqueDynamic(this, &ThisClass::OnEconomyChanged);
	EconomySubsystemRef->OnPassiveIncome.AddUniqueDynamic(this, &ThisClass::OnPassiveIncome);
	EconomySubsystemRef->OnOfflineReward.AddUniqueDynamic(this, &ThisClass::OnOfflineReward);
	//UE_LOG(LogTemp, Warning, TEXT("[UI] SoftPath=%s"), *UISettingsAsset.ToString());

	//auto* S1 = UISettingsAsset.LoadSynchronous();
	//UE_LOG(LogTemp, Warning, TEXT("[UI] LoadSynchronous -> %s"), *GetNameSafe(S1));

	//auto* S2 = LoadObject<UClickerUISettings>(nullptr, *UISettingsAsset.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("[UI] LoadObject -> %s"), *GetNameSafe(S2));

	if (!UISettingsAsset.IsNull()) {
		UE_LOG(LogTemp, Warning, TEXT("UISubsystem::Initialize Found DA"));

		if (UClickerUISettings* Settings = UISettingsAsset.LoadSynchronous()) {
			UE_LOG(LogTemp, Warning, TEXT("UISubsystem::Initialize DA Load"));

			HUDWidgetClass = Settings->HUDWidgetClass;
			ClickEffectAsset = Settings->ClickEffectAsset.LoadSynchronous();
			IdleRewardTextWidgetClass = Settings->IdleRewardTextWidgetClass;
			FloatingTextWidgetClass = Settings->FloatingTextWidgetClass;
			ClickRewardSound = Settings->ClickRewardSound.LoadSynchronous();
			OfflineRewardSound = Settings->OfflineRewardSound.LoadSynchronous();
		}
	}
}

void UClickerUISubsystem::Deinitialize() {
	if (EconomySubsystemRef) {
		EconomySubsystemRef->OnEconomyChanged.RemoveDynamic(this, &UClickerUISubsystem::OnEconomyChanged);
		EconomySubsystemRef->OnPassiveIncome.RemoveDynamic(this, &UClickerUISubsystem::OnPassiveIncome);
		EconomySubsystemRef->OnOfflineReward.RemoveDynamic(this, &UClickerUISubsystem::OnOfflineReward);
	}
	if (auto* PC = PlayerController.Get()) {
		PC->GetWorldTimerManager().ClearTimer(UpgradeSuccessTimerHandle);
	}

	HUDWidget = nullptr;
	CurrencyText = ClickValueText = UpgradeCostText = PassiveIncomeText = UpgradeSuccessText = nullptr;
	UpgradeButton = SaveButton = LoadButton = nullptr;
	EconomySubsystemRef = nullptr;
	FloatingTextPool.Empty();
	RewardTextPool.Empty();
	PlayerController.Reset();

	Super::Deinitialize();
}

void UClickerUISubsystem::ShowHUD(UWorld* World) {
	//UE_LOG(LogTemp, Warning, TEXT("ShowHUD this=%p, PC=%p, Time=%.3f"), this, PlayerController.Get(), FPlatformTime::Seconds());

	if (!World || HUDWidget || !HUDWidgetClass) return;

	if (!PlayerController.IsValid()) {
		if (auto* PC = World->GetFirstPlayerController()) {
			PlayerController = Cast<AMyPlayerController>(PC);
		}

		if (!PlayerController.IsValid()) return;
	}

	if (GEngine && GEngine->GameViewport) {
		GEngine->GameViewport->GetViewportSize(CachedViewportSize);
	}


	if (!ensureMsgf(HUDWidgetClass && HUDWidgetClass->IsChildOf(UUserWidget::StaticClass()), TEXT("HUDWidgetClass invalid: %s"), *GetNameSafe(HUDWidgetClass))) {
		return;
	}
	HUDWidget = CreateWidget<UUserWidget>(World, HUDWidgetClass);
	if (!HUDWidget) return;
	HUDWidget->AddToViewport();

	CurrencyText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("CurrencyText")));
	ClickValueText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("ClickValueText")));
	UpgradeCostText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("UpgradeCostText")));
	PassiveIncomeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("PassiveIncomeText")));
	UpgradeSuccessText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("UpgradeSuccessText")));
	UpgradeButton = Cast<UButton>(HUDWidget->GetWidgetFromName(TEXT("UpgradeButton")));
	SaveButton = Cast<UButton>(HUDWidget->GetWidgetFromName(TEXT("SaveButton")));
	LoadButton = Cast<UButton>(HUDWidget->GetWidgetFromName(TEXT("LoadButton")));

	if (UpgradeSuccessText)	UpgradeSuccessText->SetVisibility(ESlateVisibility::Collapsed);

	if (auto* PC = Cast<AMyPlayerController>(PlayerController.Get())) {
		if (UpgradeButton)
			UpgradeButton->OnClicked.AddDynamic(PC, &AMyPlayerController::OnUpgradeClicked);

		if (SaveButton)
			SaveButton->OnClicked.AddDynamic(PC, &AMyPlayerController::OnSaveClicked);

		if (LoadButton)
			LoadButton->OnClicked.AddDynamic(PC, &AMyPlayerController::OnLoadClicked);
	}


	// Make IdleRewardText Widget Pool
	const int32 PoolSize = 10;
	for (int32 i = 0; i < PoolSize; i++) {
		if (!IdleRewardTextWidgetClass) break;
		if (!ensureMsgf(IdleRewardTextWidgetClass && IdleRewardTextWidgetClass->IsChildOf(UIdleRewardTextWidget::StaticClass()), TEXT("IdleRewardTextWidgetClass invalid: %s"), *GetNameSafe(IdleRewardTextWidgetClass))) {
			return;
		}

		//for (UClass* It = IdleRewardTextWidgetClass; It; It = It->GetSuperClass())
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("[UI] IdleRewardTextWidgetClass chain: %s"), *It->GetName());
		//}
		if (auto* W = CreateWidget<UIdleRewardTextWidget>(World, IdleRewardTextWidgetClass)) {
			W->AddToViewport(10);
			W->SetVisibility(ESlateVisibility::Collapsed);
			RewardTextPool.Add(W);
		}
	}
	
	//if (EconomySubsystemRef) {
	//	OnEconomyChanged(EconomySubsystemRef->GetSnapshot());
	//	if (EconomySubsystemRef->HasPendingOfflineReward()) {
	//		OnOfflineReward(EconomySubsystemRef->GetLastOfflineReward());
	//	}
	//}	
}

void UClickerUISubsystem::ShowFloatingText(const FString& Message, const FVector& WorldLocation) {
	if (!FloatingTextWidgetClass || !PlayerController.IsValid())	return;

	FVector2D ScreenPosition;
	UGameplayStatics::ProjectWorldToScreen(PlayerController.Get(), WorldLocation, ScreenPosition);

	if (auto* FloatingWidget = GetFloatingTextWidgetFromPool()) {
		FloatingWidget->AddToViewport();
		if (auto* TextBlock = Cast<UTextBlock>(FloatingWidget->GetWidgetFromName(TEXT("FloatingText"))))
			TextBlock->SetText(FText::FromString(Message));

		if (auto* Slot = Cast<UCanvasPanelSlot>(FloatingWidget->Slot))
			Slot->SetPosition(ScreenPosition);

		if (FloatingWidget->FloatUpFade)
			FloatingWidget->PlayAnimation(FloatingWidget->FloatUpFade);

		if (auto* Controller = PlayerController.Get()) {
			FTimerHandle Temp;
			Controller->GetWorldTimerManager().SetTimer(Temp, FTimerDelegate::CreateLambda(
				[FloatingWidget]() {FloatingWidget->RemoveFromParent(); }),
				1.0f,
				false
			);
		}
	}
}

void UClickerUISubsystem::ShowIdleReward(float Amount) {
	if (auto* Widget = GetRewardWidgetFromPool()) {
		//UE_LOG(LogTemp, Warning, TEXT("UISubsystem::ShowIdleReward Called"));
		const FVector2D Center = CachedViewportSize / 2.0f;
		FVector2D RandomOffset(FMath::RandRange(-200.0f, 200.0f), FMath::RandRange(-100.0f, 100.0f));

		Widget->SetPositionInViewport(Center + RandomOffset, false);
		Widget->SetRewardAmount(Amount, false);

		Widget->SetVisibility(ESlateVisibility::Visible);
		Widget->PlayFade(0.3f, OfflineRewardSound);

		//Widget->AddToViewport(10);
	}
}

void UClickerUISubsystem::ShowClickEffect(const FVector& WorldLocation) {
	if (!PlayerController.IsValid() || !ClickEffectAsset) return;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(PlayerController->GetWorld(), ClickEffectAsset, WorldLocation, FRotator::ZeroRotator, FVector(1.0f), true, true, ENCPoolMethod::AutoRelease);
}

void UClickerUISubsystem::ShowOfflineReward(float OfflineReward) {
	UE_LOG(LogTemp, Warning, TEXT("UISubsystem::ShowOfflineReward Called"));

	if (!ensureMsgf(IdleRewardTextWidgetClass && IdleRewardTextWidgetClass->IsChildOf(UIdleRewardTextWidget::StaticClass()), TEXT("IdleRewardTextWidgetClass invalid: %s"), *GetNameSafe(IdleRewardTextWidgetClass))) {
		return;
	}

	if (!IdleRewardTextWidgetClass || !PlayerController.IsValid())	return;

	if (auto* OfflineWidget = CreateWidget<UIdleRewardTextWidget>(PlayerController.Get(), IdleRewardTextWidgetClass)) {
		OfflineWidget->SetPositionInViewport(FVector2D(CachedViewportSize.X * 0.5f, CachedViewportSize.Y * 0.15f), false);
		OfflineWidget->SetRewardAmount(OfflineReward, true);
		OfflineWidget->SetVisibility(ESlateVisibility::Visible);
		OfflineWidget->PlayFade(0.5f, OfflineRewardSound);

		OfflineWidget->AddToViewport(10);
	}
}

void UClickerUISubsystem::ShowUpgradeSuccessText() {
	if (UpgradeSuccessText && PlayerController.IsValid()) {
		UpgradeSuccessText->SetVisibility(ESlateVisibility::Visible);

		PlayerController->GetWorldTimerManager().SetTimer(
			UpgradeSuccessTimerHandle,
			this,
			&UClickerUISubsystem::HideUpgradeSuccessText,
			2.0f,
			false
		);
	}
}

void UClickerUISubsystem::HideUpgradeSuccessText() {
	if (UpgradeSuccessText) {
		UpgradeSuccessText->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UClickerUISubsystem::OnEconomyChanged(const FEconomySnapshot& Snapshot) {
	//UE_LOG(LogTemp, Warning, TEXT("UISubsystem::OnEconomyChanged Called"));	
	UpdateScore(Snapshot);
}

void UClickerUISubsystem::OnPassiveIncome(double AmountPerSec) {
	ShowIdleReward(AmountPerSec);
}

void UClickerUISubsystem::OnOfflineReward(double Amount) {
	ShowOfflineReward(Amount);
}

// private field
void UClickerUISubsystem::UpdateScore(const FEconomySnapshot& Snapshot) {
	if (CurrencyText)
		CurrencyText->SetText(FText::FromString(FString::Printf(TEXT("Currency: %.2f"), Snapshot.Currency)));

	if (ClickValueText)
		ClickValueText->SetText(FText::FromString(FString::Printf(TEXT("Click Value: %.2f"), Snapshot.CurrencyPerClick)));

	if (UpgradeCostText)
		UpgradeCostText->SetText(FText::FromString(FString::Printf(TEXT("Upgrade Cost: %.2f"), FMath::Pow(Snapshot.UpgradeGrowth, Snapshot.UpgradeLevel + 1) * Snapshot.UpgradeCostBase)));

	if (PassiveIncomeText)
		PassiveIncomeText->SetText(FText::FromString(FString::Printf(TEXT("Passive Income: %.2f / sec"), Snapshot.CurrencyPerSecond)));

}

UClickFloatingTextWidget* UClickerUISubsystem::GetFloatingTextWidgetFromPool() {
	for (auto* Widget : FloatingTextPool) {
		if (Widget && !Widget->IsInViewport()) {
			return Widget;
		}
	}

	if (FloatingTextWidgetClass && PlayerController.IsValid()) {
		if (!ensureMsgf(FloatingTextWidgetClass && FloatingTextWidgetClass->IsChildOf(UClickFloatingTextWidget::StaticClass()), TEXT("FloatingTextWidgetClass invalid: %s"), *GetNameSafe(FloatingTextWidgetClass))) {
			return nullptr;
		}

		for (UClass* It = FloatingTextWidgetClass; It; It = It->GetSuperClass())
		{
			UE_LOG(LogTemp, Warning, TEXT("[UI] FloatingTextWidgetClass chain: %s"), *It->GetName());
		}

		auto* NewWidget = CreateWidget<UClickFloatingTextWidget>(PlayerController.Get(), FloatingTextWidgetClass);
		FloatingTextPool.Add(NewWidget);
		return NewWidget;
	}

	return nullptr;
}

UIdleRewardTextWidget* UClickerUISubsystem::GetRewardWidgetFromPool() {
	int i = 0;
	for (auto* Widget : RewardTextPool) {
		//UE_LOG(LogTemp, Warning, TEXT("UISubsystem::GetRewardWidgetFromPool %d"), i);
		i++;
		//UE_LOG(LogTemp, Warning, TEXT("UISubsystem::GetRewardWidgetFromPool Looping Pool"));
		if (Widget && !Widget->IsAnimationPlaying()) {
			//UE_LOG(LogTemp, Warning, TEXT("UISubsystem::GetRewardWidgetFromPool Returning Widget"));
			return Widget;
		}
	}
	return nullptr;
}
