// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ATPCCameraModeScript.h"
#include "ATPCCMS_ChangeMovementSpeed.generated.h"


UCLASS()
class THIRDPERSONCAMERA_API UATPCCMS_ChangeMovementSpeed : public UATPCCameraModeScript
{
	GENERATED_BODY()

public:
	virtual void OnEnterCameraMode(UATPCCameraComponent* Camera) override;
	virtual void OnExitCameraMode() override;

	class UCharacterMovementComponent* GetMovementComponent(UATPCCameraComponent* Camera) const;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float NewMaxMovementSpeed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bRestoreOldMovementSpeedOnExitCameraMode = true;

	UPROPERTY(BlueprintReadOnly, Category = "ATPC")
	float OldMaxMovementSpeed = 0.f;
};
