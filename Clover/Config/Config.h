#pragma once
#include <string>

namespace Config {
    extern bool IsCharacterEditingEnabled;
    extern float CharacterEditMultiplier;
    extern bool IsNameSpoofingEnabled;
    extern std::string SpoofedName;
    extern bool IsTeleportEnabled;
    extern int IsMasterKey;
    extern bool Logs;
    extern int TeleportKey;
    extern int SpoofKey;
    extern int CharacterEditKey;
    extern bool IsInfVATSCritEnabled;
    void LoadConfig(const char* filename);
}

namespace Cheat {
    extern bool IsCharacterEditingEnabled;
    extern bool IsNameSpoofingEnabled;
    extern bool IsTeleportEnabled;
}