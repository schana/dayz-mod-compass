modded class MissionServer extends MissionBase {
    override void OnInit() {
        super.OnInit();
		GetSchanaCompassServerSettings();
		GetRPCManager().AddRPC("SchanaModCompass", "SchanaCompassServerSettingsRPC", this, SingeplayerExecutionType.Both);
	}
	
	void SchanaCompassServerSettingsRPC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		PlayerIdentity RequestedBy = PlayerIdentity.Cast(sender);
		if (RequestedBy) {
			GetRPCManager().SendRPC("SchanaModCompass", "SchanaCompassServerSettingsRPC", new Param1<SchanaCompassServerSettings>(GetSchanaCompassServerSettings()), true, RequestedBy);
		}
	}
}