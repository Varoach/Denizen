// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ablAbilityTypes.h"
#include "BaseCharacter.generated.h"

class ABaseAbilityHolder;
class UAblAbility;
class UCapsuleComponent;
class ABaseProjectile;

UCLASS()
class GAMEREAL_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void DestroyAllRotatingAbilityActors();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SpawnPoint")
	class USceneComponent* SpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CentralComponent")
	class UCentralComponent* CentralComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilityComponent")
	class UAblAbilityComponent* AbilityComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	class UCapsuleComponent* TouchingCapsule;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CastAbility"))
	void CastAbility(UAblAbility* Ability, AActor* AbilityInstigator);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Fire!"))
	void Fire();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SpawnProjectile"))
	void SpawnPointProjectile(TSubclassOf<ABaseProjectile> AbilityActorClass);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Cancel Ability"))
	void CancelAbility(UAblAbility* Ability, EAblAbilityTaskResult AbilityTaskResult);

	UFUNCTION(BlueprintCallable)
	void AddRotatingAbilityActor(TSubclassOf<ABaseAbilityActor> AbilityActorClass);

	UFUNCTION(BlueprintCallable)
	void AddRotatingAbilityActorWithStacks(TSubclassOf<ABaseAbilityActor> AbilityActorClass, int32 StackCount);

	void DeleteRotatingAbilityActor(TSubclassOf<ABaseAbilityActor> AbilityActorClass);

	UFUNCTION()
	void SpawnRotatingAbilityActor(TSubclassOf<ABaseAbilityActor> AbilityActorClass);

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_HeldActors)
	TArray<ABaseAbilityHolder*> HeldActors;

	UPROPERTY(VisibleAnywhere, Replicated)
	ABaseProjectile* HeldProjectile;

	UFUNCTION()
	virtual void OnRep_HeldActors();

};
