using UnrealBuildTool;
using System.Collections.Generic;

public class GameConceptEditorTarget : TargetRules
{
	public GameConceptEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "GameConcept" } );
	}
}
