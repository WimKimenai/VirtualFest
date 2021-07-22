using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Server)]
public class GameConceptServerTarget : TargetRules
{
    public GameConceptServerTarget(TargetInfo Target) : base(Target)
	{
        Type = TargetType.Server;
		ExtraModuleNames.AddRange( new string[] { "GameConcept" } );
	}
}
