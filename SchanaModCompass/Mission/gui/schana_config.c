class SchanaCompassServerSettings {
    protected static string DIR = "$profile:SchanaModCompass";
    protected static string PATH = DIR + "\\server-config.json";

    protected bool requireCompassItemInInventory = false;

    int GetRequireCompassItemInInventory() {
        return requireCompassItemInInventory;
    }

    void Save() {
        if (GetGame().IsServer()) {
            if (!FileExist(DIR)) {
                MakeDirectory(DIR);
            }
            JsonFileLoader<SchanaCompassServerSettings>.JsonSaveFile(PATH, this);
        }
    }

    static SchanaCompassServerSettings Get() {
        auto settings = new SchanaCompassServerSettings();
        if (FileExist(PATH)) {
            JsonFileLoader<SchanaCompassServerSettings>.JsonLoadFile(PATH, settings);
        }
        settings.Save();
        return settings;
    }
}

static ref SchanaCompassServerSettings g_SchanaCompassServerSettings;
static SchanaCompassServerSettings GetSchanaCompassServerSettings() {
    if (g_Game.IsServer() && !g_SchanaCompassServerSettings) {
        g_SchanaCompassServerSettings = SchanaCompassServerSettings.Get();
    }
    return g_SchanaCompassServerSettings;
}