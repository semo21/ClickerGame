// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actors/Defense/DefenseEnemyBase.h"

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
	
}

// Called every frame
void ADefenseEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

