modded class MissionGameplay extends MissionBase {
    private ref SchanaHeadingMenu m_SchanaHeadingMenu;

	override void OnMissionStart() {
		super.OnMissionStart();
        GetRPCManager().AddRPC("SchanaModCompass", "SchanaCompassServerSettingsRPC", this, SingleplayerExecutionType.Both);
		GetRPCManager().SendRPC("SchanaModCompass", "SchanaCompassServerSettingsRPC", new Param1<SchanaCompassServerSettings>(NULL), true, NULL);
	}
	
	void SchanaCompassServerSettingsRPC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		Param1<SchanaCompassServerSettings> data;
		if (!ctx.Read(data)) return;
		g_SchanaCompassServerSettings = data.param1;
	}
	
    override void OnUpdate (float timeslice) {
        super.OnUpdate (timeslice);

        if (GetUApi ()) {
            UAInput inp = GetUApi ().GetInputByName ("UASchanaCompassToggle");

            if (inp && inp.LocalPress () && !m_UIManager.IsMenuOpen (MENU_CHAT_INPUT)) {
                if (m_SchanaHeadingMenu) {
                    m_SchanaHeadingMenu.SchanaToggleHeading ();
                } else {
                    m_SchanaHeadingMenu = new SchanaHeadingMenu (true);
                }
            }
        }
    }
}