#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "State/AlsMovementDirection.h"
#include "AlsMath.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsSpringFloatState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	float Velocity{ ForceInit };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	float PreviousTarget{ ForceInit };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	uint8 bStateValid : 1 { false };

	void Reset()
	{
		Velocity = 0.f;
		PreviousTarget = 0.f;
		bStateValid = false;
	}
};

USTRUCT(BlueprintType)
struct ALS_API FAlsSpringVectorState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	FVector Velocity{ ForceInit };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	FVector PreviousTarget{ ForceInit };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	uint8 bStateValid : 1 { false };

	void Reset()
	{
		Velocity = FVector::ZeroVector;
		PreviousTarget = FVector::ZeroVector;
		bStateValid = false;
	}
};

UCLASS()
class ALS_API UAlsMath : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "ALS|Math", Meta = (ReturnDisplayName = "Value"))
	static float Clamp01(float Value);

	UFUNCTION(BlueprintPure, Category = "ALS|Math", Meta = (ReturnDisplayName = "Value"))
	static float LerpClamped(float From, float To, float Alpha);

	UFUNCTION(BlueprintPure, Category = "ALS|Math", Meta = (ReturnDisplayName = "Angle"))
	static float LerpAngle(float From, float To, float Alpha);

	UFUNCTION(BlueprintPure, Category = "ALS|Math", Meta = (AutoCreateRefTerm = "From, To", ReturnDisplayName = "Rotator"))
	static FRotator LerpRotator(const FRotator& From, const FRotator& To, float Alpha);

	UFUNCTION(BlueprintPure, Category = "ALS|Math", Meta = (ReturnDisplayName = "Interpolation Ammount"))
	static float Damp(float DeltaTime, float Smoothing);

	UFUNCTION(BlueprintPure, Category = "ALS|Math", Meta = (ReturnDisplayName = "Interpolation Ammount"))
	static float ExponentialDecay(float DeltaTime, float Lambda);

	template <typename ValueType>
	static ValueType Damp(const ValueType& Current, const ValueType& Target, float DeltaTime, float Smothing);

	template <typename ValueType>
	static ValueType ExponentialDecay(const ValueType& Current, const ValueType& Target, float DeltaTime, float Lambda);

	UFUNCTION(BlueprintPure, Category = "ALS|Math", Meta = (ReturnDisplayName = "Angle"))
	static float DampAngle(float Current, float Target, float DeltaTime, float Smoothing);

	UFUNCTION(BlueprintPure, Category = "ALS|Math", Meta = (ReturnDisplayName = "Angle"))
	static float ExponentialDecayAngle(float Current, float Target, float DeltaTime, float Lambda);

	UFUNCTION(BlueprintPure, Category = "ALS|Math", Meta = (AutoCreateRefTerm = "Current, Target", ReturnDisplayName = "Rotator"))
	static FRotator DampRotator(const FRotator& Current, const FRotator& Target, float DeltaTime, float Smoothing);

	UFUNCTION(BlueprintPure, Category = "ALS|Math", Meta = (AutoCreateRefTerm = "Current, Target", ReturnDisplayName = "Rotator"))
	static FRotator ExponentialDecayRotator(const FRotator& Current, const FRotator& Target, float DeltaTime, float Lambda);

	UFUNCTION(BlueprintPure, Category = "ALS|Math", Meta = (ReturnDisplayName = "Angle"))
	static float InterpolateAngleConstant(float Current, float Target, float DeltaTime, float InterpolationSpeed);

	template <typename ValueType, typename StateType>
	static ValueType SpringDamp(const ValueType& Current, const ValueType& Target, StateType& SpringState, float DeltaTime, float Frequency, float DampingRatio, float TargetVelocityAmount = 1.0f);

	UFUNCTION(BlueprintPure, Category = "ALS|Math", Meta = (ReturnDisplayName = "Value"))
	static float SpringDampFloat(float Current, float Target, UPARAM(ref) FAlsSpringFloatState& SpringState, float DeltaTime, float Frequency, float DampingRatio, float TargetVelocityAmount = 1.0f);
	
	UFUNCTION(BlueprintPure, Category = "ALS|Math", Meta = (ReturnDisplayName = "Value"))
	static FVector SpringDampVector(const FVector& Current, const FVector& Target, UPARAM(ref) FAlsSpringVectorState& SpringState, float DeltaTime, float Frequency, float DampingRatio, float TargetVelocityAmount = 1.0f);

	// Remaps the angle from the [175, 180] range to [-185, -180]. Used to
	// make the character rotate counterclockwise during a 180 degree turn.
	template <typename ValueType>
	static constexpr float RemapAngleForCounterClockwiseRotation(ValueType Angle);

	UFUNCTION(BlueprintPure, Category = "ALS|Math|Vector", Meta = (AutoCreateRefTerm = "Vector", ReturnDisplayName = "Vector"))
	static FVector ClampMagnitude01(const FVector& Vector);

	static FVector3f ClampMagnitude01(const FVector3f& Vector);

	UFUNCTION(BlueprintPure, Category = "ALS|Math|Vector", DisplayName = "Clamp Magnitude 01 2D", Meta = (AutoCreateRefTerm = "Vector", ReturnDisplayName = "Vector"))
	static FVector2D ClampMagnitude012D(const FVector2D& Vector);

	UFUNCTION(BlueprintPure, Category = "ALS|Math|Vector", Meta = (ReturnDisplayName = "Direction"))
	static FVector2D RadianToDirection(float Radian);

	UFUNCTION(BlueprintPure, Category = "ALS|Math|Vector", Meta = (ReturnDisplayName = "Direction"))
	static FVector RadianToDirectionXY(float Radian);

	UFUNCTION(BlueprintPure, Category = "ALS|Math|Vector", Meta = (ReturnDisplayName = "Direction"))
	static FVector2D AngleToDirection(float Angle);

	UFUNCTION(BlueprintPure, Category = "ALS|Math|Vector", Meta = (ReturnDisplayName = "Direction"))
	static FVector AngleToDirectionXY(float Angle);

	UFUNCTION(BlueprintPure, Category = "ALS|Math|Vector", Meta = (AutoCreateRefTerm = "Direction", ReturnDisplayName = "Angle"))
	static double DirectionToAngle(const FVector2D& Direction);

	UFUNCTION(BlueprintPure, Category = "ALS|Math|Vector", Meta = (AutoCreateRefTerm = "Direction", ReturnDisplayName = "Angle"))
	static double DirectionToAngleXY(const FVector& Direction);

	UFUNCTION(BlueprintPure, Category = "ALS|Math|Vector", Meta = (AutoCreateRefTerm = "Vecotr", ReturnDisplayName = "Vector"))
	static FVector PerpendicularClockwiseXY(const FVector& Vector);

	UFUNCTION(BlueprintPure, Category = "ALS|Math|Vector", Meta = (AutoCreateRefTerm = "Vector", ReturnDisplayName = "Vector"))
	static FVector PerpendicularCounterClockwiseXY(const FVector& Vector);

	UFUNCTION(BlueprintPure, Category = "ALS|Math|Vector", DisplayName = "Angle Between (Skip Normalization)", Meta = (AutoCreateRefTerm = "From, To", ReturnDisplayName = "Angle"))
	static double AngleBetweenSkipNormalization(const FVector& From, const FVector& To);

	UFUNCTION(BlueprintPure, Category = "ALS|Math|Vector", DisplayName = "Slerp (Skip Normalization)", Meta = (AutoCreateRefTerm = "From, To", ReturnDisplayName = "Direction"))
	static FVector SlerpSkipNormalization(const FVector& From, const FVector& To, float Alpha);

	UFUNCTION(BlueprintCallable, Category = "ALS|Math|Input", Meta = (ReturnDisplayName = "Direction"))
	static EAlsMovementDirection CalculateMovementDirection(float Angle, float ForwardHalfAngle, float AngleThreshold);

	// Calculates the projection location and direction of the perpendicular to AC through B.
	UFUNCTION(BlueprintCallable, Category = "ALS|Math|Input", Meta = (AutoCreateRefTerm = "ALocation, bLocation, CLocation", ExpandBoolAsExecs = "ReturnValue"))
	static bool TryCalculatePoleVector(const FVector& ALocation, const FVector& BLocation, const FVector& CLocation, FVector& ProjectionLocation, FVector& Direction);

public:
	static constexpr auto CounterClockwiseRotationAngleThreshold{ 5.f };
};

template <typename ValueType>
ValueType UAlsMath::Damp(const ValueType& Current, const ValueType& Target, float DeltaTime, float Smothing)
{
	return Smothing > 0.0f ? FMath::Lerp(Current, Target, Damp(DeltaTime, Smothing)) : Target;
}

template <typename ValueType>
ValueType UAlsMath::ExponentialDecay(const ValueType& Current, const ValueType& Target, float DeltaTime, float Lambda)
{
	return Lambda > 0.0f ? FMath::Lerp(Current, Target, ExponentialDecay(DeltaTime, Lambda)) : Target;
}

template <>
inline FRotator UAlsMath::Damp(const FRotator& Current, const FRotator& Target, const float DeltaTime, const float Smoothing)
{
	return Smoothing > 0.0f ? LerpRotator(Current, Target, Damp(DeltaTime, Smoothing)) : Target;
}

template <>
inline FRotator UAlsMath::ExponentialDecay(const FRotator& Current, const FRotator& Target, const float DeltaTime, const float Lambda)
{
	return Lambda > 0.0f ? LerpRotator(Current, Target, ExponentialDecay(DeltaTime, Lambda)) : Target;
}

template <typename ValueType, typename StateType>
ValueType UAlsMath::SpringDamp(const ValueType& Current, const ValueType& Target, StateType& SpringState, float DeltaTime, float Frequency, float DampingRatio, float TargetVelocityAmount /*= 1.0f*/)
{
	if (DeltaTime <= UE_SMALL_NUMBER) {
		return Current;
	}

	if (!SpringState.bStateValid) {
		SpringState.Velocity = ValueType{ 0.0f };
		SpringState.PreviousTarget = Target;
		SpringState.bStateValid = true;

		return Target;
	}

	ValueType Result{ Current };
	FMath::SpringDamper(Result, SpringState.Velocity, Target, (Target - SpringState.PreviousTarget) * Clamp01(TargetVelocityAmount) / DeltaTime, DeltaTime, Frequency, DampingRatio);
	SpringState.PreviousTarget = Target;

	return Result;
}

template <typename ValueType>
constexpr float UAlsMath::RemapAngleForCounterClockwiseRotation(ValueType Angle)
{
	if (Angle > 180.0f - CounterClockwiseRotationAngleThreshold) {
		return Angle - 360.0f;
	}

	return Angle;
}

