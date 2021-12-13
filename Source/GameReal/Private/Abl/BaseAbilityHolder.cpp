// Fill out your copyright notice in the Description page of Project Settings.


#include "Abl/BaseAbilityHolder.h"
#include "Abl/BaseAbilityActor.h"
#include "Components/SplineComponent.h"
#include "BaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SceneComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABaseAbilityHolder::ABaseAbilityHolder()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//SetReplicateMovement(true);

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent = SceneComponent;

	RotatingSceneComponent = CreateDefaultSubobject<USceneComponent>("RotatingSceneComponent");
	RotatingSceneComponent->SetupAttachment(RootComponent);

	RotatingSceneComponent->SetUsingAbsoluteRotation(true);

	SplineComponent = CreateDefaultSubobject<USplineComponent>("SplineComponent");
	SplineComponent->SetupAttachment(RotatingSceneComponent);

	AttachSlot = CreateDefaultSubobject<USceneComponent>("AttachSlot");
	AttachSlot->SetupAttachment(SplineComponent);

	bReplicates = true;

	NetUpdateFrequency = 66.f;
	MinNetUpdateFrequency = 33.f;

}

// Called when the game starts or when spawned
void ABaseAbilityHolder::BeginPlay()
{
	Super::BeginPlay();
	RotatingSceneComponent->SetWorldRotation(UKismetMathLibrary::RandomRotator(true));
	AttachSlot->SetRelativeLocation(SplineComponent->GetLocationAtSplineInputKey(1.f, ESplineCoordinateSpace::Local));
	if (GetLocalRole() == ROLE_Authority)
	{
		UE_LOG(LogTemp, Warning, TEXT("WE GOT AUTHORITY"));
	}

}

// Called every frame
void ABaseAbilityHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SplineComponent)
	{
		SplineComponent->AddRelativeRotation(FRotator(0, 2, 0));

		if (SplineComponent->GetRelativeRotation().Yaw >= 360)
		{
			SplineComponent->SetRelativeRotation(FRotator::ZeroRotator);
		}
	}
	

}

ABaseAbilityActor* ABaseAbilityHolder::AttachActor(ABaseAbilityActor* ActorToAttach)
{
	if (ActorToAttach)
	{
		AttachedActor = ActorToAttach;
	}

	return AttachedActor;

}

ABaseAbilityActor* ABaseAbilityHolder::GetAttachedActor() const
{
	return AttachedActor;
}

void ABaseAbilityHolder::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseAbilityHolder, AttachedActor);

}

void ABaseAbilityHolder::BeginDestroy()
{
	if (AttachedActor && !AttachedActor->IsActorBeingDestroyed())
	{
		AttachedActor->Destroy();
	}

	Super::BeginDestroy();
}
