// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MazeGen : ModuleRules
{
	public MazeGen(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
