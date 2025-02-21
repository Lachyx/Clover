#include <clover.h>

HANDLE CharacterThread = NULL;
HANDLE SpoofNameThread = NULL;
HANDLE TeleportYThread = NULL;

HWND MainWindowHandle = NULL;

DWORD WINAPI Func() {
    Log("Hello it seems you have decompiled this DLL?", INFO);
    Config::LoadConfig("Clover.ini");
    MessageBox(NULL, "Made By Lucky.xyz", "Credits", MB_OK | MB_ICONINFORMATION);

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        MainWindowHandle = FindWindow(NULL, "Fallout76");

        if (GetForegroundWindow() != MainWindowHandle) {
            continue;
        }
       
        if (GetAsyncKeyState(Config::IsMasterKey)) {
            if (GetAsyncKeyState(Config::CharacterEditKey) && Config::IsCharacterEditingEnabled) {
                Cheat::IsCharacterEditingEnabled = !Cheat::IsCharacterEditingEnabled;

                if (Cheat::IsCharacterEditingEnabled)
                {
                    MessageBeep(0xFFFFFF);
                    CharacterThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CharacterEdit, NULL, 0, NULL);
                    Log("CharacterEdit thread started", INFO);
                }
                else
                {
                    MessageBeep(0xFFFFFF);
                    CloseHandle(CharacterThread);
                    CharacterThread = NULL;
                    Log("CharacterEdit thread terminated.", INFO);

                };          
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
            }
            else if (GetAsyncKeyState(Config::SpoofKey) && Config::IsNameSpoofingEnabled) {
                Cheat::IsNameSpoofingEnabled = !Cheat::IsNameSpoofingEnabled;

                if (Cheat::IsNameSpoofingEnabled) {
                    MessageBeep(0xFFFFFF);
                    SpoofNameThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SpoofName, NULL, 0, NULL);
                    Log("Spoof Thread Started", INFO);
                }
                else {
                    MessageBeep(0xFFFFFF);
                    CloseHandle(SpoofNameThread);
                    SpoofNameThread = NULL;
                    Log("Spoof Thread Ended", INFO);
                };
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
            }
            else if (GetAsyncKeyState(Config::TeleportKey) && Config::IsTeleportEnabled) {
                Cheat::IsTeleportEnabled = !Cheat::IsTeleportEnabled;

                if (Cheat::IsTeleportEnabled && Config::IsTeleportEnabled) {
                    MessageBeep(0xFFFFFF);
                    TeleportYThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TeleportY, NULL, 0, NULL);
                    Log("Teleport Thread Started", INFO);
                }
                else {
                    MessageBeep(0xFFFFFF);
                    CloseHandle(TeleportYThread);
                    TeleportYThread = NULL;
                    Log("Teleport Thread Ended", INFO);
                };
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
            }
        }
        InfVATSCrit();
    }
    Log("Func thread exiting.", INFO);
    ExitThread(0);
}