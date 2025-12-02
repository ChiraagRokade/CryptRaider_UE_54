// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CryptRaider_UE_54 : ModuleRules
{
	public CryptRaider_UE_54(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
