// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actors/Defense/DefenseGridManager.h"

// Sets default values
ADefenseGridManager::ADefenseGridManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADefenseGridManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefenseGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

