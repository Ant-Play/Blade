// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "ATPCCameraBaseObject.h"
#include "ATPCCameraShakesObject.generated.h"

class UCameraShakeBase;

UCLASS(classGroup = "ATPC")
class THIRDPERSONCAMERA_API UATPCCameraShakesObject : public UATPCCameraBaseObject
{
	GENERATED_BODY()

public:
	virtual void OnEnterCameraMode(bool bWithInterpolation) override;
	virtual void OnExitCameraMode() override;
protected:
	/*
	* @return - key: isInfinite, value: duration
	*/
	TPair<bool, float> GetCameraShakeDuration(TSubclassOf<UCameraShakeBase> CameraShake) const;

	void PlayCameraShake(TSubclassOf<UCameraShakeBase> CameraShake);
	void OnCameraShakeEnd();
protected:
	bool bPlayRegularCameraMode = false;
	FTimerHandle CameraShakeEndTimerHandle;
};
