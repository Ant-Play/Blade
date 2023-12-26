// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ATPCCameraBaseObject.h"
#include "ATPCCameraFOVObject.generated.h"

UCLASS(classGroup = "ATPC")
class THIRDPERSONCAMERA_API UATPCCameraFOVObject : public UATPCCameraBaseObject
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void Validate(bool bWithInterpolation) override;
	virtual void OnEnterCameraMode(bool bWithInterpolation) override;

	virtual void SwitchToCineCamera() override;

	UFUNCTION(BlueprintPure, Category = "ATPC")
	float GetCurrentFov() const;
protected:
	virtual void UpdateFOV(bool bWithInterpolation, float DeltaTime);
	
};
