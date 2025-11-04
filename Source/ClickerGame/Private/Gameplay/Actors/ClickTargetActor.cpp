// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actors/ClickTargetActor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AClickTargetActor::AClickTargetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube"));
	if (MeshAsset.Succeeded()) {
		Mesh->SetStaticMesh(MeshAsset.Object);
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
		Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	}

}

// Called when the game starts or when spawned
void AClickTargetActor::BeginPlay()
{
	Super::BeginPlay();	
}

void AClickTargetActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}