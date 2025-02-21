#include <clover.h>

static HRESULT(__stdcall* pCreateDXGIFactory)(REFIID riid, void** ppFactory) = nullptr;
static HRESULT(__stdcall* pCreateDXGIFactory1)(REFIID riid, void** ppFactory) = nullptr;
static HRESULT(__stdcall* pCreateDXGIFactory2)(UINT flags, REFIID riid, void** ppFactory) = nullptr;
static HRESULT(__stdcall* pDXGID3D10CreateDevice)(HMODULE hModule, void* pFactory, void* pAdapter, UINT Flags, void* pUnknown, void** ppDevice) = nullptr;
static HRESULT(__stdcall* pDXGID3D10CreateLayeredDevice)(void* pUnknown1, void* pUnknown2, void* pUnknown3, void* pUnknown4, void* pUnknown5) = nullptr;
static SIZE_T(__stdcall* pDXGID3D10GetLayeredDeviceSize)(const void* pLayers, UINT NumLayers) = nullptr;
static HRESULT(__stdcall* pDXGID3D10RegisterLayers)(const void* pLayers, UINT NumLayers) = nullptr;

extern "C" {
    __declspec(dllexport) HRESULT __stdcall CreateDXGIFactory(REFIID riid, void** ppFactory) {
        static volatile unsigned long long InitCount = 0;
        if (InterlockedIncrement(&InitCount) == 1)
        {
			CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Func, NULL, 0, nullptr));
        }
        return pCreateDXGIFactory(riid, ppFactory);
    }

    __declspec(dllexport) HRESULT __stdcall CreateDXGIFactory1(REFIID riid, void** ppFactory) {
        return pCreateDXGIFactory1(riid, ppFactory);
    }

    __declspec(dllexport) HRESULT __stdcall CreateDXGIFactory2(UINT flags, REFIID riid, void** ppFactory) {
        return pCreateDXGIFactory2(flags, riid, ppFactory);
    }

    __declspec(dllexport) HRESULT __stdcall DXGID3D10CreateDevice(HMODULE hModule, void* pFactory, void* pAdapter, UINT Flags, void* pUnknown, void** ppDevice) {
        return pDXGID3D10CreateDevice(hModule, pFactory, pAdapter, Flags, pUnknown, ppDevice);
    }

    __declspec(dllexport) HRESULT __stdcall DXGID3D10CreateLayeredDevice(void* pUnknown1, void* pUnknown2, void* pUnknown3, void* pUnknown4, void* pUnknown5) {
        return pDXGID3D10CreateLayeredDevice(pUnknown1, pUnknown2, pUnknown3, pUnknown4, pUnknown5);
    }

    __declspec(dllexport) SIZE_T __stdcall DXGID3D10GetLayeredDeviceSize(const void* pLayers, UINT NumLayers) {
        return pDXGID3D10GetLayeredDeviceSize(pLayers, NumLayers);
    }

    __declspec(dllexport) HRESULT __stdcall DXGID3D10RegisterLayers(const void* pLayers, UINT NumLayers) {
        return pDXGID3D10RegisterLayers(pLayers, NumLayers);
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	UNREFERENCED_PARAMETER(hinstDLL);
	UNREFERENCED_PARAMETER(lpvReserved);

	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		char dllPath[MAX_PATH];
		ZeroMemory(dllPath, sizeof(dllPath));
		GetSystemDirectoryA(dllPath, sizeof(dllPath));
		strcat_s(dllPath, "\\dxgi.dll");

		HMODULE dxgi = LoadLibraryA(dllPath);
		if (!dxgi)
		{
			return FALSE;
		}

		*(void**)&pCreateDXGIFactory = GetProcAddress(dxgi, "CreateDXGIFactory");
		*(void**)&pCreateDXGIFactory1 = GetProcAddress(dxgi, "CreateDXGIFactory1");
		*(void**)&pCreateDXGIFactory2 = GetProcAddress(dxgi, "CreateDXGIFactory2");
		*(void**)&pDXGID3D10CreateDevice = GetProcAddress(dxgi, "DXGID3D10CreateDevice");
		*(void**)&pDXGID3D10CreateLayeredDevice = GetProcAddress(dxgi, "DXGID3D10CreateLayeredDevice");
		*(void**)&pDXGID3D10GetLayeredDeviceSize = GetProcAddress(dxgi, "DXGID3D10GetLayeredDeviceSize");
		*(void**)&pDXGID3D10RegisterLayers = GetProcAddress(dxgi, "DXGID3D10RegisterLayers");
	}
	break;
	default:
		break;
	}

	return TRUE;
}