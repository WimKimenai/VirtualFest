using UnrealBuildTool;
using System.Collections.Generic;

public class GameConceptTarget : TargetRules
{
	public GameConceptTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "GameConcept" } );
	}
}
