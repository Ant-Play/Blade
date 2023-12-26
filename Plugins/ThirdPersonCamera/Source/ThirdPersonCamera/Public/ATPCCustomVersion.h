// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/Guid.h"

// Custom serialization version for all packages containing Third Person Camera dependent asset types
struct THIRDPERSONCAMERA_API FATPCCustomVersion
{
	enum Type
	{
		// Before any version changes were made in the plugin
		BeforeCustomeVersionWasAdded = 0,

		NewInterpolationTypes,

		// -----<new versions can be added above this line>-------------------------------------------------
		VersionPlusOne,
		LastestVersion = VersionPlusOne - 1
	};

	// The GUID for this custom version number
	static const FGuid GUID;
private:
	FATPCCustomVersion() {}
};
