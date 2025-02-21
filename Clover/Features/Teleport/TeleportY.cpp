#include <clover.h>

void TeleportY() {
    Log("Teleport Y enabled.", INFO);

    uintptr_t Address = 0x0602BCD0;
    std::vector<uintptr_t> offsets = { 0x4C0, 0x78 };

    while (Cheat::IsTeleportEnabled) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        if (GetAsyncKeyState(Config::IsMasterKey)) {

            uintptr_t yCoordAddress = ResolveAddress(Address, offsets);

            float currentY = *reinterpret_cast<float*>(yCoordAddress);

            if (GetAsyncKeyState(VK_UP)) {
                currentY += 10.0f;
                Log("Teleported 10f up", INFO);
            }
            else if (GetAsyncKeyState(VK_DOWN)) {
                currentY -= 10.0f;
                Log("Teleported 10f down", INFO);
            }
            else if (GetAsyncKeyState(VK_RIGHT)) {
                currentY = 999.0f;
                Log("Teleported To Max Y");
            }
            *reinterpret_cast<float*>(yCoordAddress) = currentY;
        };
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    ExitThread(0);
    Log("TeleportY thread exiting.", INFO);
}