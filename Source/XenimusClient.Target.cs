// Copyright Big Woof Studios, LLC. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class XenimusClientTarget : TargetRules
{
	public XenimusClientTarget(TargetInfo Target) : base(Target)
	{
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
        Type = TargetType.Client;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Xenimus" } );
	}
}
