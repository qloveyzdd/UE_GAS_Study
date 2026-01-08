// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE_GAS_Study : ModuleRules
{
	public UE_GAS_Study(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		OptimizeCode = CodeOptimization.Never;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
			"GameplayAbilities",
			"GameplayTasks",
			"GameplayTags",
			"Slate",
			"SlateCore",
			"HTTP",
			"JsonUtilities",
			"Json",
			"ModularGameplay",
			"UMG",
		});
	}
}
