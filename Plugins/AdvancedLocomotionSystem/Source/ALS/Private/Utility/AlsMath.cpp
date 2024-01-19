#include "Utility/AlsMath.h"

inline float UAlsMath::Clamp01(float Value)
{
	return Value <= 0.0f ? 0.0f : Value >= 1.0f ? 1.0f : Value;
}

inline float UAlsMath::LerpClamped(float From, float To, float Alpha)
{
	return From + (To - From) * Clamp01(Alpha);
}

inline float UAlsMath::LerpAngle(float From, float To, float Alpha)
{
	auto Delta{FRotator3f::NormalizeAxis(To - From)};
	Delta = RemapAngleForCounterClockwiseRotation(Delta);

	return FRotator3f::NormalizeAxis(From + Delta * Alpha);
}

inline FRotator UAlsMath::LerpRotator(const FRotator& From, const FRotator& To, float Alpha)
{
	auto Result{ To - From };
	Result.Normalize();

	Result.Pitch = RemapAngleForCounterClockwiseRotation(Result.Pitch);
	Result.Yaw = RemapAngleForCounterClockwiseRotation(Result.Yaw);
	Result.Roll = RemapAngleForCounterClockwiseRotation(Result.Roll);

	Result *= Alpha;
	Result += From;
	Result.Normalize();

	return Result;
}

inline float UAlsMath::Damp(float DeltaTime, float Smoothing)
{
	// https://www.rorydriscoll.com/2016/03/07/frame-rate-independent-damping-using-lerp/
	return 1.0f - FMath::Pow(Smoothing, DeltaTime);
}

inline float UAlsMath::ExponentialDecay(float DeltaTime, float Lambda)
{
	// https://www.rorydriscoll.com/2016/03/07/frame-rate-independent-damping-using-lerp/
	return 1.0f - FMath::InvExpApprox(Lambda * DeltaTime);
}

inline float UAlsMath::DampAngle(float Current, float Target, float DeltaTime, float Smoothing)
{
	return Smoothing > 0.0f ? LerpAngle(Current, Target, Damp(DeltaTime, Smoothing)) : Target;
}

inline float UAlsMath::ExponentialDecayAngle(float Current, float Target, float DeltaTime, float Lambda)
{
	return Lambda > 0.0f ? LerpAngle(Current, Target, ExponentialDecay(DeltaTime, Lambda)) : Target;
}

inline FRotator UAlsMath::DampRotator(const FRotator& Current, const FRotator& Target, float DeltaTime, float Smoothing)
{
	return Damp(Current, Target, DeltaTime, Smoothing);
}

inline FRotator UAlsMath::ExponentialDecayRotator(const FRotator& Current, const FRotator& Target, float DeltaTime, float Lambda)
{
	return ExponentialDecay(Current, Target, DeltaTime, Lambda);
}

inline float UAlsMath::InterpolateAngleConstant(float Current, float Target, float DeltaTime, float InterpolationSpeed)
{
	if (InterpolationSpeed <= 0.0f || Current == Target) {
		return Target;
	}

	auto Delta{FRotator3f::NormalizeAxis(Target - Current)};
	Delta = RemapAngleForCounterClockwiseRotation(Delta);

	const auto Alpha{DeltaTime * InterpolationSpeed};

	return FRotator3f::NormalizeAxis(Current + FMath::Clamp(Delta, -Alpha, Alpha));
}

inline float UAlsMath::SpringDampFloat(float Current, float Target, FAlsSpringFloatState& SpringState, float DeltaTime, float Frequency, float DampingRatio, float TargetVelocityAmount /*= 1.0f*/)
{
	return SpringDamp(Current, Target, SpringState, DeltaTime, Frequency, DampingRatio, TargetVelocityAmount);
}

inline FVector UAlsMath::SpringDampVector(const FVector& Current, const FVector& Target, FAlsSpringVectorState& SpringState, float DeltaTime, float Frequency, float DampingRatio, float TargetVelocityAmount /*= 1.0f*/)
{
	return SpringDamp(Current, Target, SpringState, DeltaTime, Frequency, DampingRatio, TargetVelocityAmount);
}

inline FVector UAlsMath::ClampMagnitude01(const FVector& Vector)
{
	const auto MagnitudeSquared{Vector.SizeSquared()};

	if (MagnitudeSquared <= 1.0f) {
		return Vector;
	}

	const auto Scale{FMath::InvSqrt(MagnitudeSquared)};

	return {Vector.X * Scale, Vector.Y * Scale, Vector.Z * Scale};
}

inline FVector3f UAlsMath::ClampMagnitude01(const FVector3f& Vector)
{
	const auto MagnitudeSquared{Vector.SizeSquared()};

	if (MagnitudeSquared <= 1.0f) {
		return Vector;
	}

	const auto Scale{FMath::InvSqrt(MagnitudeSquared)};

	return {Vector.X * Scale, Vector.Y * Scale, Vector.Z * Scale};
}

inline FVector2D UAlsMath::ClampMagnitude012D(const FVector2D& Vector)
{
	const auto MagnitudeSquared{Vector.SizeSquared()};

	if (MagnitudeSquared <= 1.0f) {
		return Vector;
	}

	const auto Scale{FMath::InvSqrt(MagnitudeSquared)};

	return {Vector.X * Scale, Vector.Y * Scale};
}

inline FVector2D UAlsMath::RadianToDirection(float Radian)
{
	float Sin, Cos;
	FMath::SinCos(&Sin, &Cos, Radian);

	return {Cos, Sin};
}

inline FVector UAlsMath::RadianToDirectionXY(float Radian)
{
	float Sin, Cos;
	FMath::SinCos(&Sin, &Cos, Radian);

	return {Cos, Sin, 0.0f};
}

inline FVector2D UAlsMath::AngleToDirection(float Angle)
{
	return RadianToDirection(FMath::DegreesToRadians(Angle));
}

inline FVector UAlsMath::AngleToDirectionXY(float Angle)
{
	return RadianToDirectionXY(FMath::DegreesToRadians(Angle));
}

inline double UAlsMath::DirectionToAngle(const FVector2D& Direction)
{
	return FMath::RadiansToDegrees(FMath::Atan2(Direction.Y, Direction.X));
}

inline double UAlsMath::DirectionToAngleXY(const FVector& Direction)
{
	return FMath::RadiansToDegrees(FMath::Atan2(Direction.Y, Direction.X));
}

inline FVector UAlsMath::PerpendicularClockwiseXY(const FVector& Vector)
{
	return {Vector.Y, -Vector.X, Vector.Z};
}

FVector UAlsMath::PerpendicularCounterClockwiseXY(const FVector& Vector)
{
	return {-Vector.Y, Vector.X, Vector.Z};
}

inline double UAlsMath::AngleBetweenSkipNormalization(const FVector& From, const FVector& To)
{
	return FMath::RadiansToDegrees(FMath::Acos(From | To));
}

inline FVector UAlsMath::SlerpSkipNormalization(const FVector& From, const FVector& To, float Alpha)
{
	// http://allenchou.net/2018/05/game-math-deriving-the-slerp-formula/
	const auto Dot{From | To};

	if (Dot > 0.9995f || Dot < -0.9995f) {
		return FMath::Lerp(From, To, Alpha).GetSafeNormal();
	}

	const auto Theta{UE_REAL_TO_FLOAT(FMath::Acos(Dot)) * Alpha};

	float Sin, Cos;
	FMath::SinCos(&Sin, &Cos, Theta);

	const auto FromPerpendicular{(To - From * Dot).GetSafeNormal()};

	return From * Cos + FromPerpendicular * Sin;
}

inline EAlsMovementDirection UAlsMath::CalculateMovementDirection(float Angle, float ForwardHalfAngle, float AngleThreshold)
{
	if (Angle >= -ForwardHalfAngle - AngleThreshold && Angle <= ForwardHalfAngle + AngleThreshold) {
		return EAlsMovementDirection::Forward;
	}

	if (Angle >= ForwardHalfAngle - AngleThreshold && Angle <= 180.0f - ForwardHalfAngle + AngleThreshold) {
		return EAlsMovementDirection::Right;
	}

	if (Angle >= -180.0f + ForwardHalfAngle - AngleThreshold && Angle <= -ForwardHalfAngle + AngleThreshold) {
		return EAlsMovementDirection::Left;
	}

	return EAlsMovementDirection::Backward;
}

inline bool UAlsMath::TryCalculatePoleVector(const FVector& ALocation, const FVector& BLocation, const FVector& CLocation, FVector& ProjectionLocation, FVector& Direction)
{
	const auto AbVector{BLocation - ALocation};
	if (AbVector.IsNearlyZero()) {
		// Can't do anything if A and B are equal.
		ProjectionLocation = ALocation;
		Direction = FVector::ZeroVector;

		return false;
	}

	auto AcVector{CLocation - ALocation};
	if (AcVector.IsNearlyZero()) {
		// Only A and C are equal.

		ProjectionLocation = ALocation;
		Direction = AbVector.GetUnsafeNormal(); // A and B are not equal, so normalization will be safe.

		return true;
	}

	ProjectionLocation = ALocation + AbVector.ProjectOnToNormal(AcVector);
	Direction = BLocation - ProjectionLocation;

	return Direction.Normalize(); // Direction will be zero and cannot be normalized if A, B and C are collinear.
}
