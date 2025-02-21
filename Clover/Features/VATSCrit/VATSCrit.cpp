#include <clover.h>

void InfVATSCrit() {
    if (Config::IsInfVATSCritEnabled) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        if (GetAsyncKeyState(VK_SPACE)) {
            uintptr_t Address = 0x0602BCD0;
            std::vector<uintptr_t> offsets = { 0x100, 0x0, 0x8B0 };

            const auto IsInVATSAddress = ResolveAddress(0x05E96120, { 0x0, 0xC0, 0x198 });
            if (IsInVATSAddress == 0) {
                Log("Failed to resolve IsInVATSAddress.", CRITICAL);
                return;
            }

            const int isInVATS = *reinterpret_cast<int*>(IsInVATSAddress);

            if (isInVATS != 1 && isInVATS != 17409) {
                Log("User is not in VATS. isInVATS value: " + std::to_string(isInVATS), INFO);
                return;
            }

            uintptr_t VATSCritChargeAddress = ResolveAddress(Address, offsets);
            if (VATSCritChargeAddress == 0) {
                Log("Failed to resolve VATSCritChargeAddress.", CRITICAL);
                return;
            }

            uintptr_t isValid = *reinterpret_cast<uintptr_t*>(VATSCritChargeAddress);
            if (!isValid) return;

            *reinterpret_cast<float*>(VATSCritChargeAddress) = 100.0f;
            Log("VATSCrit charge set to 100.0", INFO);
        }
    }
}
