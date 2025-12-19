// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Space_Sorcerer : ModuleRules
{
	public Space_Sorcerer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Space_Sorcerer",
			"Space_Sorcerer/Variant_Horror",
			"Space_Sorcerer/Variant_Horror/UI",
			"Space_Sorcerer/Variant_Shooter",
			"Space_Sorcerer/Variant_Shooter/AI",
			"Space_Sorcerer/Variant_Shooter/UI",
			"Space_Sorcerer/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
