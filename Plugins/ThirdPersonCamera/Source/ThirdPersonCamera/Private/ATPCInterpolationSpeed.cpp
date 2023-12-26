// Fill out your copyright notice in the Description page of Project Settings.


#include "ATPCInterpolationSpeed.h"


void FATPCInterploationSpeed::InterpolateSpeed(float DeltaTime)
{
	if (bUseInterpSpeedToInterpolation)
	{
		CurrentInterpSpeed = FMath::FInterpConstantTo(CurrentInterpSpeed, InterpolationSpeed, DeltaTime, InterpSpeedToInterpolation);
	}
}

float FATPCInterploationSpeed::GetCurrentInterpolationSpeed() const
{
	return bUseInterpSpeedToInterpolation ? CurrentInterpSpeed : InterpolationSpeed;
}

void FATPCInterploationSpeed::ResetCurrentSpeed()
{
	if (bUseInterpSpeedToInterpolation)
	{
		CurrentInterpSpeed = 0.f;
	}
}

FString FATPCInterploationSpeed::ToString() const
{
	return FString::Printf(TEXT("InterpolationSpeed: %.2f, InterpSpeedToInterpolation: %.2f, CurrentInterpSpeed: %.2f"), InterpolationSpeed, InterpSpeedToInterpolation, CurrentInterpSpeed);
	//return FString::Printf(TEXT("%.2f"), GetCurrentInterpolationSpeed());
}
