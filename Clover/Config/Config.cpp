#include "Config.h"
#include <clover.h>

namespace Config {
    bool IsCharacterEditingEnabled = false;
    float CharacterEditMultiplier = 0.23f;
    bool IsNameSpoofingEnabled = false;
    std::string SpoofedName = "Bethesda Developer";
    bool IsTeleportEnabled = false;
    int IsMasterKey = VK_CONTROL;
    int TeleportKey = VK_F1;
    int SpoofKey = VK_F2;
    int CharacterEditKey = VK_F3;
    bool Logs = false;
    bool IsInfVATSCritEnabled = false;

    void LoadConfig(const char* filename) {
        std::ifstream file(filename);
        if (!file) {
            Log("Not Config File You Fucked Up Setup", CRITICAL);
            return;
        }

        std::string line, currentSection;

        std::unordered_map<std::string, std::function<void(const std::string&)>> settingHandlers = {
            {"Logs",                    [](const std::string& val) { Logs = (val == "true"); }},
            {"CharacterEditingEnabled", [](const std::string& val) { IsCharacterEditingEnabled = (val == "true"); }},
            {"CharacterEditMultiplier", [](const std::string& val) { CharacterEditMultiplier = std::stof(val); }},
            {"NameSpoofingEnabled",     [](const std::string& val) { IsNameSpoofingEnabled = (val == "true"); }},
            {"InfiniteVATSCrit",        [](const std::string& val) { IsInfVATSCritEnabled = (val == "true"); }},
            {"SpoofedName",             [](const std::string& val) { SpoofedName = val; }},
            {"TeleportEnabled",         [](const std::string& val) { IsTeleportEnabled = (val == "true"); }},
            {"MasterKey",               [](const std::string& val) { IsMasterKey = std::stoi(val); }},
            {"TeleportKey",             [](const std::string& val) { TeleportKey = std::stoi(val); }},
            {"SpoofKey",                [](const std::string& val) { SpoofKey = std::stoi(val); }},
            {"CharactetEditKey",        [](const std::string& val) { CharacterEditKey = std::stoi(val); }},
        };



        while (std::getline(file, line)) {
            line = line.substr(0, line.find(';'));
            line.erase(0, line.find_first_not_of(" \t\r\n"));
            line.erase(line.find_last_not_of(" \t\r\n") + 1);
            if (line.empty()) continue;

            if (line.front() == '[' && line.back() == ']') {
                currentSection = line.substr(1, line.size() - 2);
            }
            else if (currentSection == "Config") {
                size_t eqPos = line.find('=');
                if (eqPos == std::string::npos) continue;

                std::string key = line.substr(0, eqPos);
                std::string value = line.substr(eqPos + 1);
                key.erase(0, key.find_first_not_of(" \t\r\n"));
                key.erase(key.find_last_not_of(" \t\r\n") + 1);
                value.erase(0, value.find_first_not_of(" \t\r\n"));
                value.erase(value.find_last_not_of(" \t\r\n") + 1);

                if (settingHandlers.find(key) != settingHandlers.end()) {
                    settingHandlers[key](value);
                }
            }
        }
    }
}

namespace Cheat {
    bool IsCharacterEditingEnabled = false;
    bool IsNameSpoofingEnabled = false;
    bool IsTeleportEnabled = false;
}