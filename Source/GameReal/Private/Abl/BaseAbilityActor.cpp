// Fill out your copyright notice in the Description page of Project Settings.


#include "Abl/BaseAbilityActor.h"

// Sets default values
ABaseAbilityActor::ABaseAbilityActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = ActorMesh;
	bReplicates = true;
	NetUpdateFrequency = 66.f;
	MinNetUpdateFrequency = 33.f;

}

// Called when the game starts or when spawned
void ABaseAbilityActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseAbilityActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseAbilityActor::Activate(AActor* Character)
{

}


