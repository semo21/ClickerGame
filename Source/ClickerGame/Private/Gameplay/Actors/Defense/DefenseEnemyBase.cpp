// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Actors/Defense/DefenseEnemyBase.h"
#include "Gameplay/Actors/Defense/DefenseGridManager.h"

#include "Engine/DamageEvents.h"

// Sets default values
ADefenseEnemyBase::ADefenseEnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void ADefenseEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentHP = MaxHP;
	
}

// Called every frame
void ADefenseEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GridManager) return;	
	if (PathStep >= CurrentPath.Num()) { 
		OnReachedGoal.Broadcast();
		Destroy();
		return;
	}
	FVector Target = GridManager->TileIndexToWorld(CurrentPath[PathStep]);
	const FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), Target, DeltaTime, MoveSpeed);
	SetActorLocation(NewLocation);
	if (FVector::Dist(NewLocation, Target) < 1.0f) ++PathStep;
	
}

float ADefenseEnemyBase::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	const float AppliedDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (AppliedDamage <= 0.0f || CurrentHP <= 0.0f) return 0.0f;

	CurrentHP -= AppliedDamage;
	UE_LOG(LogTemp, Warning, TEXT("ADefenseEnemyBase::TakeDamage: Remaining HP %f"), CurrentHP);

	if (CurrentHP <= 0.0f) Destroy();
		
	return AppliedDamage;
}

void ADefenseEnemyBase::InitPath(ADefenseGridManager* InGrid) {
	if (!InGrid) return;
	GridManager = InGrid;
	CurrentPath = InGrid->GetCurrentPath();
	PathStep = 1;	

	GridManager->OnPathChanged.AddUObject(this, &ADefenseEnemyBase::HandlePathChanged);

}

void ADefenseEnemyBase::HandlePathChanged() {
	if (!GridManager || !CurrentPath.IsValidIndex(PathStep)) return;
	TArray<int32> NewPath = GridManager->FindPathToGoal(CurrentPath[PathStep]);

	if (NewPath.IsEmpty()) {
		return;
	}

	CurrentPath = NewPath;
	PathStep = 0;
}