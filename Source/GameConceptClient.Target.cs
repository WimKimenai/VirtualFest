using UnrealBuildTool;
using System.Collections.Generic;

public class GameConceptClientTarget : TargetRules
{
	public GameConceptClientTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Client;
		ExtraModuleNames.AddRange( new string[] { "GameConcept" } );
	}
}
