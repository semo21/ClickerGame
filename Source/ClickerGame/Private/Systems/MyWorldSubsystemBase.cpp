// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/MyWorldSubsystemBase.h"

#include "GameFramework/GameModeBase.h"
#include "GameFramework/WorldSettings.h"

void UMyWorldSubsystemBase::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Log, TEXT("%s::Initialize / World: %s"), *GetClass()->GetName(), *GetWorld()->GetName());
}

bool UMyWorldSubsystemBase::ShouldCreateSubsystem(UObject* Outer) const {
	if (!Super::ShouldCreateSubsystem(Outer)) return false;

	const TSubclassOf<AGameModeBase> RequiredClass = GetRequiredGameModeClass();
	if (!RequiredClass) return false;

	const UWorld* World = Cast<UWorld>(Outer);
	const AWorldSettings* Settings = World ? World->GetWorldSettings(false, false) : nullptr;

	if (!Settings || !Settings->DefaultGameMode) return false;

	return Settings->DefaultGameMode->IsChildOf(RequiredClass);
}

bool UMyWorldSubsystemBase::DoesSupportWorldType(const EWorldType::Type WorldType) const {
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}
