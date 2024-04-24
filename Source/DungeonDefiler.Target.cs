// Copyright Siddharth Jaiswal

using UnrealBuildTool;
using System.Collections.Generic;

public class DungeonDefilerTarget : TargetRules
{
	public DungeonDefilerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "DungeonDefiler" } );
	}
}
