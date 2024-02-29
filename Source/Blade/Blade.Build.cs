// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Blade : ModuleRules
{
	public Blade(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "MotionWarping", "ThirdPersonCamera", "ALS"});
		PublicIncludePaths.AddRange(new string[] {"ThirdPersonCamera/Public"});
	}
}
