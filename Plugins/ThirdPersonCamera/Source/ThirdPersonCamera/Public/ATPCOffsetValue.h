// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ATPCFunctionLibrary.h"
#include "ATPCInterpolationSpeed.h"
#include "CoreMinimal.h"

template<typename TValueType>
struct FATPCOffsetValue
{
public:
	FATPCOffsetValue();

	void Interpolate(bool bWithInterp, float DeltaTime);
public:
	TValueType Current;
	TValueType Target;
	FATPCInterploationSpeed InterpolationSpeed;
private:
	TValueType InterpolateImpl(float DeltaTime);
};

template<typename TValueType>
FATPCOffsetValue<TValueType>::FATPCOffsetValue()
	: Current(TValueType()), Target(TValueType()), InterpolationSpeed(0.f) {}

template<>
inline FATPCOffsetValue<FVector>::FATPCOffsetValue()
	: Current(FVector::ZeroVector), Target(FVector::ZeroVector), InterpolationSpeed(0.f) {}

template<>
inline FATPCOffsetValue<FRotator>::FATPCOffsetValue()
	: Current(FRotator::ZeroRotator), Target(FRotator::ZeroRotator), InterpolationSpeed(0.f) {}

template<typename TValueType>
void FATPCOffsetValue<TValueType>::Interpolate(bool bWithInterp, float DeltaTime)
{
	if (bWithInterp)
	{
		Current = InterpolateImpl(DeltaTime);
	}
	else
	{
		Current = Target;
	}
}

template<typename TValueType>
TValueType FATPCOffsetValue<TValueType>::InterpolateImpl(float DeltaTime)
{
	return UATPCFunctionLibrary::InterpFloat(Current, Target, DeltaTime, InterpolationSpeed);
}

template<>
inline FVector FATPCOffsetValue<FVector>::InterpolateImpl(float DeltaTime)
{
	return UATPCFunctionLibrary::InterpVector(Current, Target, DeltaTime, InterpolationSpeed);
}

template<>
inline FRotator FATPCOffsetValue<FRotator>::InterpolateImpl(float DeltaTime)
{
	return UATPCFunctionLibrary::InterpRotator(Current, Target, DeltaTime, InterpolationSpeed);
}

using FATPCFloatOffset = FATPCOffsetValue<float>;
using FATPCVectorOffset = FATPCOffsetValue<FVector>;
using FATPCRotatorOffset = FATPCOffsetValue<FRotator>;
