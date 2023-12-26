// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraModeScript/ATPCCMS_ChangeMovementSpeed.h"

#include "ATPCCameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UATPCCMS_ChangeMovementSpeed::OnEnterCameraMode(UATPCCameraComponent* Camera)
{
	Super::OnEnterCameraMode(Camera);

	

	if (UCharacterMovementComponent* movementComponent = GetMovementComponent(Camera))
	{
		if (bRestoreOldMovementSpeedOnExitCameraMode)
		{
			OldMaxMovementSpeed = movementComponent->MaxWalkSpeed;
		}

		movementComponent->MaxWalkSpeed = NewMaxMovementSpeed;
	}
}

void UATPCCMS_ChangeMovementSpeed::OnExitCameraMode()
{
	Super::OnExitCameraMode();

	if (bRestoreOldMovementSpeedOnExitCameraMode)
	{
		if (UCharacterMovementComponent* movementComponent = GetMovementComponent(OwningCamera))
		{
			movementComponent->MaxWalkSpeed = OldMaxMovementSpeed;
		}
	}
}

class UCharacterMovementComponent* UATPCCMS_ChangeMovementSpeed::GetMovementComponent(UATPCCameraComponent* Camera) const
{
	ACharacter* character = Camera != nullptr ? Cast<ACharacter>(Camera->GetOwner()) : nullptr;
	if (character != nullptr)
	{
		return character->GetCharacterMovement();
	}
	else
	{
		return nullptr;
	}
}
