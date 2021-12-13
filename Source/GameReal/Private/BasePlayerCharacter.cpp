// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePlayerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"

ABasePlayerCharacter::ABasePlayerCharacter()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraEye"));
	CameraComponent->SetupAttachment(RootComponent);

	ArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmMesh"));
	ArmMesh->SetupAttachment(CameraComponent);

	SpawnPoint->SetupAttachment(CameraComponent);

	//FVector CameraLocation(0, 0, BaseEyeHeight);
	//CameraComponent->SetRelativeLocation(CameraLocation);
}

void ABasePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsLocallyControlled())
	{
		FRotator NewRot = FRotator::ZeroRotator;
		NewRot.Pitch = RemoteViewPitch * 360.0f / 255.0f;

		CameraComponent->SetRelativeRotation(NewRot);
	}

}
