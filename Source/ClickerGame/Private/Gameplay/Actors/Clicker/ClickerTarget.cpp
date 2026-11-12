// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actors/Clicker/ClickerTarget.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AClickerTarget::AClickerTarget()
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

void AClickerTarget::HandleClicked(const FVector& HitLocation) {
	if (ClickEffect) {
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ClickEffect, HitLocation, FRotator::ZeroRotator, FVector(1.0f), true, true, ENCPoolMethod::AutoRelease);
	}
	if (ClickSound) {
		UGameplayStatics::PlaySoundAtLocation(this, ClickSound, HitLocation);
	}
}

// Called when the game starts or when spawned
void AClickerTarget::BeginPlay()
{
	Super::BeginPlay();	
}

void AClickerTarget::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}