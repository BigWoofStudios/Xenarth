// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Xenimus : ModuleRules
{
	public Xenimus(ReadOnlyTargetRules target) : base(target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine",
			"InputCore", "EnhancedInput",
			"NetCore",
			"MotionWarping", "MotionTrajectory",
			"GameplayAbilities"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"GameplayTags", "GameplayTasks",
			"ModularGameplay", "GameFeatures",
			"Niagara",
			"OnlineSubsystem", "OnlineSubsystemSteam",
			"NavigationSystem",
			"AIModule"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
