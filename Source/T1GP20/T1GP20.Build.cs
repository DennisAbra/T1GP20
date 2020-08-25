// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class T1GP20 : ModuleRules
{
	public T1GP20(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
