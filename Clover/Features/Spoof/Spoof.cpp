#include <clover.h>

void SpoofName(const char* name) {
    Log("Spoof Thread Enabled", INFO);

    uintptr_t Address = 0x05DE5ED0;
    std::vector<uintptr_t> offsets = { 0x28, 0x48, 0x0, 0x0 };

    while (Cheat::IsNameSpoofingEnabled) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        name = Config::SpoofedName.c_str();

        uintptr_t SpoofAddress = ResolveAddress(Address, offsets);

        strncpy_s(reinterpret_cast<char*>(SpoofAddress), 25, name, _TRUNCATE);
    }

    ExitThread(0);
    Log("Spoof Thread Exited", INFO);
}