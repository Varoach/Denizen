// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "CentralComponent.h"
#include "Abl/BaseAbilityActor.h"
#include "Abl/BaseAbilityHolder.h"
#include "Components/SplineComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "ablAbilityComponent.h"
#include "BaseProjectile.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(RootComponent);

	CentralComponent = CreateDefaultSubobject<UCentralComponent>(TEXT("CentralComponent"));
	CentralComponent->SetIsReplicated(true);
	CentralComponent->SetupAttachment(RootComponent);

	AbilityComponent = CreateDefaultSubobject<UAblAbilityComponent>(TEXT("AbilityComp"));

	TouchingCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TouchingCapsuleComp"));
	TouchingCapsule->SetupAttachment(GetCapsuleComponent());

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	//TouchingCapsule->SetCapsuleRadius(GetCapsuleComponent()->GetUnscaledCapsuleRadius() + 10);
	//TouchingCapsule->SetCapsuleHalfHeight(GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() + 10);
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::OnRep_HeldActors()
{
	return;
}

void ABaseCharacter::CastAbility(UAblAbility* Ability, AActor* AbilityInstigator)
{
	UAblAbilityContext* NewContext = UAblAbilityContext::MakeContext(Ability, AbilityComponent, this, AbilityInstigator);
	AbilityComponent->ActivateAbility(NewContext);

}

void ABaseCharacter::Fire()
{
	if (HeldProjectile)
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile: %s"), *HeldProjectile->GetName());
		HeldProjectile->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		HeldProjectile->Fire();
		HeldProjectile = nullptr;
	}
}

void ABaseCharacter::SpawnPointProjectile(TSubclassOf<ABaseProjectile> AbilityActorClass)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		FActorSpawnParameters SpawnParams;
		HeldProjectile = GetWorld()->SpawnActor<ABaseProjectile>(AbilityActorClass, FVector::ZeroVector, SpawnPoint->GetComponentRotation(), SpawnParams);
		HeldProjectile->AttachToComponent(SpawnPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

void ABaseCharacter::CancelAbility(UAblAbility* Ability, EAblAbilityTaskResult AbilityTaskResult)
{
	AbilityComponent->CancelAbility(Ability, AbilityTaskResult);

}

void ABaseCharacter::AddRotatingAbilityActor(TSubclassOf<ABaseAbilityActor> AbilityActorClass)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		SpawnRotatingAbilityActor(AbilityActorClass);
	}

}

void ABaseCharacter::AddRotatingAbilityActorWithStacks(TSubclassOf<ABaseAbilityActor> AbilityActorClass, int32 StackCount)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		while (HeldActors.Num() < StackCount)
		{
			SpawnRotatingAbilityActor(AbilityActorClass);
		}
	}
}

void ABaseCharacter::DeleteRotatingAbilityActor(TSubclassOf<ABaseAbilityActor> AbilityActorClass)
{
	for (ABaseAbilityHolder* AbilityHolder : HeldActors)
	{
		if (AbilityHolder->GetAttachedActor()->GetClass() == AbilityActorClass)
		{
			if (GetLocalRole() == ROLE_Authority)
			{
				HeldActors.Remove(AbilityHolder);
				AbilityHolder->GetAttachedActor()->Destroy();
				AbilityHolder->Destroy();
				return;
			}
		}
	}
}

void ABaseCharacter::SpawnRotatingAbilityActor(TSubclassOf<ABaseAbilityActor> AbilityActorClass)
{
	FActorSpawnParameters SpawnParams;

	ABaseAbilityHolder* NewArm = GetWorld()->SpawnActor<ABaseAbilityHolder>(ABaseAbilityHolder::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

	NewArm->AttachToComponent(CentralComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	ABaseAbilityActor* AbilityActor = GetWorld()->SpawnActor<ABaseAbilityActor>(AbilityActorClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

	NewArm->AttachActor(AbilityActor);

	AbilityActor->AttachToComponent(NewArm->AttachSlot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	HeldActors.Add(NewArm);
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseCharacter, HeldActors);
	DOREPLIFETIME(ABaseCharacter, HeldProjectile);

}

void ABaseCharacter::DestroyAllRotatingAbilityActors()
{
	if (GetLocalRole() == ROLE_Authority)
	{
	TArray<ABaseAbilityHolder*> TempArray = HeldActors;
	for (ABaseAbilityHolder* AbilityHolder : TempArray)
	{
			AbilityHolder->GetAttachedActor()->Destroy();
			AbilityHolder->Destroy();
	}
	HeldActors.Empty();
	}
}
