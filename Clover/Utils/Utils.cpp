#include <clover.h>

std::string ToHex(uintptr_t value) {
    std::stringstream ss;
    ss << "0x" << std::hex << std::uppercase << value;
    return ss.str();
}

uintptr_t GetBaseModuleAddress(const char* ModuleName) {
    return reinterpret_cast<uintptr_t>(GetModuleHandle(ModuleName));
}

uintptr_t ResolveAddress(uintptr_t Address, const std::vector<uintptr_t>& offsets) {
    uintptr_t BaseModule = GetBaseModuleAddress("Fallout76.exe");
    if (!BaseModule) { return 0; }

    uintptr_t ResolvedAddress = BaseModule + Address;

    for (uintptr_t offset : offsets) {
        ResolvedAddress = *reinterpret_cast<uintptr_t*>(ResolvedAddress);
        if (!ResolvedAddress) return 0;

        ResolvedAddress += offset;
    }
    return ResolvedAddress;
};

//uintptr_t CheckGameVersion() {
//    Log("Check Game Version Func", INFO);
//    Sleep(1500);
//    const char* ExpectedGameVersion = Game::CurrentVersion;
//    uintptr_t Address = 0x05DE0510;
//    std::vector<uintptr_t> offsets = { 0x28, 0x20, 0x170, 0xAEC };
//
//    uintptr_t GameVersionAddress = ResolveAddress(Address, offsets);
//    const auto CurrentGameVersion = reinterpret_cast<const char*>(GameVersionAddress);
//
//    if (strcmp(CurrentGameVersion, ExpectedGameVersion) != 0) {
//        Log("Game Has Updated. Please Wait For Update. Exiting...", CRITICAL);
//        MessageBox(NULL, "Cheat Is Out Of Date. Please wait for an update.", "Cheat Update Required", MB_OK | MB_ICONWARNING);
//        ExitThread(0);
//    }
//
//    Log("Game Up To Date.", INFO);
//}