// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actors/Portal.h"
#include "Components/BoxComponent.h"
#include "Gameplay/Character/MyCharacter.h"

// Sets default values
APortal::APortal()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));

	InteractionBox->SetupAttachment(Root);

	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	InteractionBox->SetGenerateOverlapEvents(true);

	

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnBoxBeginOverlap);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &APortal::OnBoxEndOverlap);
	
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortal::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(OtherActor)) {
		PlayerCharacter->SetCurrentPortal(this);
		UE_LOG(LogTemp, Warning, TEXT("Portal Enter"));
	}
}

void APortal::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(OtherActor)) {
		PlayerCharacter->ClearCurrentPortal(this);
		UE_LOG(LogTemp, Warning, TEXT("Portal Exit"));
	}	
}

void APortal::Interact() {
	UE_LOG(LogTemp, Warning, TEXT("Portal Interact"));
}

