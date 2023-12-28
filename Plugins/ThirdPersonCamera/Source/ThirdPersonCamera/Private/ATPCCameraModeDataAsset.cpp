// Fill out your copyright notice in the Description page of Project Settings.


#include "ATPCCameraModeDataAsset.h"

#include "ATPCCustomVersion.h"

void UATPCCameraModeDataAsset::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	Ar.UsingCustomVersion(FATPCCustomVersion::GUID);

	if (Ar.IsLoading())
	{
		const int32 customVer = Ar.CustomVer(FATPCCustomVersion::GUID);

		if (customVer < FATPCCustomVersion::NewInterpolationTypes)
		{
			auto replaceInterpolationSpeed = [](FATPCInterploationSpeed& NewInterpSpeed, const float OldInterpSpeed, TOptional<EATPCInterpolationType> OldInterpType = {}, TOptional<float> InterpSpeedToInterpolation = {}) {
				NewInterpSpeed.InterpolationSpeed = OldInterpSpeed;

				if (OldInterpType.IsSet())
				{
					NewInterpSpeed.InterpolationType = OldInterpType.GetValue();
				}
				
				if (InterpSpeedToInterpolation.IsSet())
				{
					NewInterpSpeed.InterpSpeedToInterpolation = InterpSpeedToInterpolation.GetValue();
				}
			};

			//--------REPLACE LOCATION SETTINGS--------//
			auto& locationSettings = CameraModeSettings.LocationSettings;

			// if here not working, using old method
			replaceInterpolationSpeed(locationSettings.ZoomInterpolation, locationSettings.ZoomInterpolation.InterpolationSpeed, locationSettings.ZoomInterpolation.InterpolationType);

			replaceInterpolationSpeed(locationSettings.SocketOffsetInterpolation, locationSettings.SocketOffsetInterpolation.InterpolationSpeed);

			replaceInterpolationSpeed(locationSettings.TargetOffsetInterpolation, locationSettings.TargetOffsetInterpolation.InterpolationSpeed);

			//--------REPLACE ROTATION SETTINGS--------//
			auto& rotationSettings = CameraModeSettings.RotationSettings;

			// if here not working, using old method
			replaceInterpolationSpeed(rotationSettings.ViewInterpolation, rotationSettings.ViewInterpolation.InterpolationSpeed);

			replaceInterpolationSpeed(rotationSettings.RotationOffsetSettings.RotationInterpolation, rotationSettings.RotationOffsetSettings.RotationInterpolation.InterpolationSpeed, rotationSettings.RotationOffsetSettings.RotationInterpolation.InterpolationType);
			
			replaceInterpolationSpeed(rotationSettings.ViewRotationToActorRotationSettings.RotationInterpolation, rotationSettings.ViewRotationToActorRotationSettings.RotationInterpolation.InterpolationSpeed, EATPCInterpolationType::SmoothInterpolation, rotationSettings.ViewRotationToActorRotationSettings.RotationInterpolation.InterpSpeedToInterpolation);

			//--------REPLACE FOV SETTINGS--------//
			// if here not working, using old method
			replaceInterpolationSpeed(CameraModeSettings.FOVSettings.FOVInterpolation, CameraModeSettings.FOVSettings.FOVInterpolation.InterpolationSpeed);

			//--------REPLACE FOLLOW TO TERRAIN SETTINGS--------//
			auto& followTerraionSettings = CameraModeSettings.FollowTerrainSettings;

			// if here not working, using old method
			replaceInterpolationSpeed(followTerraionSettings.SocketOffsetInterpolation, followTerraionSettings.SocketOffsetInterpolation.InterpolationSpeed);
			replaceInterpolationSpeed(followTerraionSettings.PitchRotationInterpolation, followTerraionSettings.PitchRotationInterpolation.InterpolationSpeed);

			//--------REPLACE LOCK ON TARGET SETTINGS--------//
			auto& lockOnTargetSettings = CameraModeSettings.LockOnTargetSettings;

			// if here not working, using old method
			replaceInterpolationSpeed(lockOnTargetSettings.CameraRotationInterpolation, lockOnTargetSettings.CameraRotationInterpolation.InterpolationSpeed, EATPCInterpolationType::SmoothInterpolation, lockOnTargetSettings.CameraRotationInterpolation.InterpSpeedToInterpolation);
		}
	}
}
