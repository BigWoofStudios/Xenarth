// Copyright Big Woof Studios, LLC. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class XenimusServerTarget : TargetRules
{
	public XenimusServerTarget(TargetInfo Target) : base(Target)
	{
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
        Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Xenimus" } );
	}
}
