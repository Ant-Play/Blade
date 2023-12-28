// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraModeScript/ATPCCMS_RotateActorToTarget.h"

#include "ATPCCameraComponent.h"
#include "ATPCCameraLockOnTargetObject.h"
#include "GameFramework/Actor.h"

UATPCCMS_RotateActorToTarget::UATPCCMS_RotateActorToTarget()
{
	bEnableTick = true;
	TickGroup = EATPCCameraModeScriptTickGroup::PreCameraObjectTick;
}

void UATPCCMS_RotateActorToTarget::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto lockOnTargetObject = OwningCamera != nullptr ? OwningCamera->GetCameraLockOnTargetObject() : nullptr;
	if (lockOnTargetObject == nullptr)
	{
		return;
	}

	AActor* targetActor = lockOnTargetObject->GetTargetActor();
	if (targetActor == nullptr)
	{
		return;
	}

	AActor* sourceActor = OwningCamera->GetOwner();

	FRotator sourceRotation = sourceActor->GetActorRotation();
	sourceRotation.Pitch = 0.f;
	sourceRotation.Roll = 0.f;

	auto sourceToTargetRotation = FRotationMatrix::MakeFromX(targetActor->GetActorLocation() - sourceActor->GetActorLocation()).Rotator();
	sourceToTargetRotation.Pitch = 0.f;
	sourceToTargetRotation.Roll = 0.f;

	auto resultRotation = sourceActor->GetActorRotation();
	resultRotation.Yaw = FMath::RInterpTo(sourceRotation, sourceToTargetRotation, DeltaSeconds, RotationSpeed).Yaw;

	sourceActor->SetActorRotation(resultRotation);
}
