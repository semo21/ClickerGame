// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actors/Defense/DefenseTowerBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADefenseTowerBase::ADefenseTowerBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Root);

}

