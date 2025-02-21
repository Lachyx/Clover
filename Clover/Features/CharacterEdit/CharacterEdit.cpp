#include <clover.h>

void CharacterEdit() {
    Log("Character editing enabled.", INFO);

    uintptr_t Address = 0x05DE7700;
    std::vector<uintptr_t> offsets = { 0x2C };

    while (Cheat::IsCharacterEditingEnabled) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        if (!GetAsyncKeyState(VK_LBUTTON))
            continue;

        uintptr_t chargenAddress = ResolveAddress(Address,offsets);

        *reinterpret_cast<float*>(chargenAddress) = Config::CharacterEditMultiplier;
    }
    ExitThread(0);
    Log("CharacterEdit thread exiting.", INFO);
}