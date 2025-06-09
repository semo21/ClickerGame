// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickerComponent.h"
#include "Engine/Engine.h"	
#include "MyPlayerController.h"

// Sets default values for this component's properties
UClickerComponent::UClickerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ClickCount = 0;
	Currency = 0.0f;
	CurrencyPerClick = 1.0f; // Default value for currency earned per click
	CurrencyPerSecond = 2.0f;
	UpgradeCost = 10.0f;
	AccumulatedTime = 0.0f;

}


// Called when the game starts
void UClickerComponent::BeginPlay()
{
	Super::BeginPlay();


}


// Called every frame
void UClickerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AccumulatedTime += DeltaTime;
	if (AccumulatedTime >= 1.0f) 
	{
		Currency += CurrencyPerSecond;
		AccumulatedTime = 0.0f;

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,
			FString::Printf(TEXT("Passive Income! Currency: %.2f"), Currency));

		if (APlayerController* PC = GetWorld()->GetFirstPlayerController()) {
			AMyPlayerController* MyPC = Cast<AMyPlayerController>(PC);
			if (MyPC) {
				MyPC->UpdateCurrencyUI();
			}
		}

	}
}

void UClickerComponent::HandleClick() {
	UE_LOG(LogTemp, Warning, TEXT("Currency before: %.2f"), Currency);
	
	ClickCount++;
	Currency += ClickValue;

	UE_LOG(LogTemp, Warning, TEXT("Currency after: %.2f"), Currency);



	GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Green,
		FString::Printf(TEXT("Clicked! Count: %d | Currency: %.2f"), ClickCount, Currency));
}

void UClickerComponent::HandleUpgrade() {
	UE_LOG(LogTemp, Warning, TEXT("Click detected!")); // 아주 기본적인 영어 로그
	FString Message = TEXT("Click logic started");
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
	if (Currency >= UpgradeCost) {
		Currency -= UpgradeCost;
		ClickValue += 1.0f;
		UpgradeCost *= 1.5f;
		UE_LOG(LogTemp, Log, TEXT("업그레이드 성공! 현재 클릭당 수익: %f"), ClickValue);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("통화 부족!"));
	}
}

float UClickerComponent::GetCurrency() const {
	return Currency;
}

float UClickerComponent::GetClickValue() const {
	return ClickValue;
}

float UClickerComponent::GetUpgradeCost() const {
	return UpgradeCost;
}