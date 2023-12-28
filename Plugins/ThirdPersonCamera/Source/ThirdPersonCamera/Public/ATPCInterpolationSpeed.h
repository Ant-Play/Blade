// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ATPCInterpolationSpeed.generated.h"

UENUM(BlueprintType)
enum class EATPCInterpolationType : uint8
{
	SmoothInterpolation, //Interpolation via  FMath::FInterpTo
	ConstInterpolation   //Interpolation via FMath::FInterpConstantTo
};

/**
 * Interpolation speed with self interpolation value
 * For correct get @InterpolationSpeed in BP use InterpolationSpeed_GetCurrentInterpolationSpeed function. For C++ use GetCurrentInterpolationSpeed function
 */
 USTRUCT(BlueprintType)
struct THIRDPERSONCAMERA_API FATPCInterploationSpeed
{
	GENERATED_BODY()

public:
	FATPCInterploationSpeed() = default;
	FATPCInterploationSpeed(float InInterpSpeed) : InterpolationSpeed(InInterpSpeed) {}
public:
	float CurrentInterpSpeed = 0.f;

	/** Interpolation speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float InterpolationSpeed = 1.f;

	/** Interpolation type */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	EATPCInterpolationType InterpolationType = EATPCInterpolationType::SmoothInterpolation;

	/** If true, @InterpSpeed will be interpolated with speed @InterpSpeedToInterpolation and reset after interpolation result value is equals to interpolation target value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InlineEditConditionToggle))
	bool bUseInterpSpeedToInterpolation = true;

	/** See @bUseInterpSpeedToInterpolation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0", UIMin = "0.0", EditCondition = "bUseInterpSpeedToInterpolation"))
	float InterpSpeedToInterpolation = 1.f;

	/** Tolerance between result and target interpolation value for reset @InterpSpeed. See @bUseInterpSpeedToInterpolation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0", UIMin = "0.0", EditCondition = "bUseInterpSpeedToInterpolation"))
	float ResetInterpSpeedTolerance = 0.15f;

public:
	void InterpolateSpeed(float DeltaTime);

	float GetCurrentInterpolationSpeed() const;

	void ResetCurrentSpeed();

	FString ToString() const;
};
