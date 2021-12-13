// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseAbilityHolder.generated.h"

UCLASS()
class GAMEREAL_API ABaseAbilityHolder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseAbilityHolder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Replicated)
	class ABaseAbilityActor* AttachedActor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SceneComponent")
	class USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SceneComponent")
	class USceneComponent* AttachSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RotatingSceneComponent")
	class USceneComponent* RotatingSceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SplineComponent")
	class USplineComponent* SplineComponent;

	UFUNCTION(BlueprintCallable)
	ABaseAbilityActor* AttachActor(ABaseAbilityActor* ActorToAttach);

	UFUNCTION(BlueprintCallable)
	ABaseAbilityActor* GetAttachedActor() const;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginDestroy();

};
