// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TrickShot : ModuleRules
{
	public TrickShot(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
