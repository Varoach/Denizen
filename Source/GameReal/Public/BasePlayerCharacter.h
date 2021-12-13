// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BasePlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GAMEREAL_API ABasePlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	ABasePlayerCharacter();

	public:
		// Called every frame
		virtual void Tick(float DeltaTime) override;

	protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
		class UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
		class USkeletalMeshComponent* ArmMesh;

	public:

	USkeletalMeshComponent* GetArmmesh() const { return ArmMesh; }

	UCameraComponent* GetFirstPersonCameraComponent() const { return CameraComponent; }

	TArray<AActor*> HeldProjectiles;
	
};
