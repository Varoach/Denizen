// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseAbilityActor.generated.h"

UCLASS()
class GAMEREAL_API ABaseAbilityActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseAbilityActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Activate(AActor* Character);

	bool Rotate = false;

	FRotator RotationAngle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	class UStaticMeshComponent* ActorMesh;

};
