// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ATPCCameraModeScript.h"
#include "ATPCCMS_PawnUseControllerRot.generated.h"

/** Override params @OrientRotationToMovement and @UseControllerDesiredRotation in CharacterMovementComponent */
UCLASS()
class THIRDPERSONCAMERA_API UATPCCMS_PawnUseControllerRot : public UATPCCameraModeScript
{
	GENERATED_BODY()

public:
	virtual void OnEnterCameraMode(UATPCCameraComponent* Camera) override;
	virtual void OnExitCameraMode() override;

	class UCharacterMovementComponent* GetMovementComponent(UATPCCameraComponent* Camera) const;

public:
	/** Set @OrientRotationToMovement to CharacterMovementComponent */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool OrientRotationToMovement = false;

	/** Set @UseControllerDesiredRotation to CharacterMovementComponent */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool UseControllerDesiredRotation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bResetoreOldValuesOnExitCameraMode = true;

	UPROPERTY(BlueprintReadOnly, Category = "ATPC")
	bool OldOrientRotationToMovement = false;

	UPROPERTY(BlueprintReadOnly, Category = "ATPC")
	bool OldUseControllerDesiredRotation = false;
};
