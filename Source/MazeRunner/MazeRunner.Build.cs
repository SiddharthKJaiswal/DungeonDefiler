// Copyright Siddharth Jaiswal

using UnrealBuildTool;

public class MazeRunner : ModuleRules
{
	public MazeRunner(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule" });

		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}