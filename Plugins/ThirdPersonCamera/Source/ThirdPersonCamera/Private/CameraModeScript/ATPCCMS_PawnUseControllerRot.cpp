// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraModeScript/ATPCCMS_PawnUseControllerRot.h"

#include "ATPCCameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UATPCCMS_PawnUseControllerRot::OnEnterCameraMode(UATPCCameraComponent* Camera)
{
	Super::OnEnterCameraMode(Camera);

	if (auto movementComponent = GetMovementComponent(Camera))
	{
		if (bResetoreOldValuesOnExitCameraMode)
		{
			OldOrientRotationToMovement = movementComponent->bOrientRotationToMovement;
			OldUseControllerDesiredRotation = movementComponent->bUseControllerDesiredRotation;
		}

		movementComponent->bOrientRotationToMovement = OrientRotationToMovement;
		movementComponent->bUseControllerDesiredRotation = UseControllerDesiredRotation;
	}
}

void UATPCCMS_PawnUseControllerRot::OnExitCameraMode()
{
	Super::OnExitCameraMode();

	if (bResetoreOldValuesOnExitCameraMode)
	{
		if (auto movementComponent = GetMovementComponent(OwningCamera))
		{
			movementComponent->bOrientRotationToMovement = OldOrientRotationToMovement;
			movementComponent->bUseControllerDesiredRotation = OldUseControllerDesiredRotation;
		}
	}
}

class UCharacterMovementComponent* UATPCCMS_PawnUseControllerRot::GetMovementComponent(UATPCCameraComponent* Camera) const
{
	auto character = Camera != nullptr ? Cast<ACharacter>(Camera->GetOwner()) : nullptr;
	return character != nullptr ? character->GetCharacterMovement() : nullptr;
}
