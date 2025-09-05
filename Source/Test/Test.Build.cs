// Test.Build.cs

using UnrealBuildTool;

public class Test : ModuleRules
{
    public Test(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
            {
				// Initial Modules
				"Core", "CoreUObject", "Engine", "InputCore",
            }
        );

        PrivateDependencyModuleNames.AddRange(new string[] { });

    }
}
