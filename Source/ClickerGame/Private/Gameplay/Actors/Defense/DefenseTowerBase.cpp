// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actors/Defense/DefenseTowerBase.h"

#include "Gameplay/Actors/Defense/DefenseEnemyBase.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"

// Sets default values
ADefenseTowerBase::ADefenseTowerBase(){
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Root);

}

void ADefenseTowerBase::BeginPlay() {
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ADefenseTowerBase::Attack, AttackInterval, true);
}

ADefenseEnemyBase* ADefenseTowerBase::FindTarget() const {
	ADefenseEnemyBase* NearestEnemy = nullptr;
	float NearestDistSq = Range * Range;
	const FVector TowerLocation = GetActorLocation();

	for (TActorIterator<ADefenseEnemyBase> It(GetWorld()); It; ++It) {
		ADefenseEnemyBase* Enemy = *It;
		const float DistSq = FVector::DistSquared2D(TowerLocation, Enemy->GetActorLocation());

		if (DistSq <= NearestDistSq) {
			NearestDistSq = DistSq;
			NearestEnemy = Enemy;
		}
	}

	return NearestEnemy;
}

void ADefenseTowerBase::Attack() {
	ADefenseEnemyBase* Target = FindTarget();
	if (!Target) return;

	DrawDebugLine(GetWorld(), GetActorLocation(), Target->GetActorLocation(), FColor::Red, false, 0.2f, 0, 2.0f);
	UGameplayStatics::ApplyDamage(Target, Damage, nullptr, this, nullptr);
}