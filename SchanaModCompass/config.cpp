class CfgPatches
{
	class SchanaModCompass
	{
		requiredAddons[] = {};
		units[] = {};
		weapons[] = {};
	};
};

class CfgMods
{
	class SchanaModCompass
	{
		name = "SchanaModCompass";
		action = "https://github.com/schana/dayz-mod-compass";
		author = "schana";
		type = "mod";
		inputs = "SchanaModCompass/Data/Inputs.xml";
		dependencies[] =
		{
			"Mission"
		};
		class defs
		{
			class missionScriptModule
			{
				files[] =
				{
					"SchanaModCompass/Mission"
				};
			};
		};
	};
};
