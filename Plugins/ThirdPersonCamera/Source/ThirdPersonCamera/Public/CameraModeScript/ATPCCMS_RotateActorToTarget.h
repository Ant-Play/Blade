// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ATPCCameraModeScript.h"
#include "ATPCCMS_RotateActorToTarget.generated.h"

/* Rotate actor to target from UATPCCameraLockOnTargetObject */
UCLASS()
class THIRDPERSONCAMERA_API UATPCCMS_RotateActorToTarget : public UATPCCameraModeScript
{
	GENERATED_BODY()

public:
	UATPCCMS_RotateActorToTarget();

	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float RotationSpeed = 1.5f;
};
