#include <Windows.h>
#include "types.h"
#include "SafeWrite.h"
#include "patches.h"

HMODULE hLibrary;

 HRESULT WINAPI DirectInput8Create(
    HINSTANCE hinst,
    DWORD dwVersion,
    REFIID riidltf,
    LPVOID *ppvOut,
    LPUNKNOWN punkOuter) {

    if(hLibrary)  {
        const auto originalProc = GetProcAddress(hLibrary, "DirectInput8Create");
        if(originalProc)  {
            return reinterpret_cast<HRESULT(WINAPI *)(HINSTANCE, DWORD, REFIID, LPVOID *, LPUNKNOWN)>(originalProc)(hinst, dwVersion, riidltf, ppvOut, punkOuter);
        }
    }

    return E_FAIL;
}



BOOL WINAPI DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch(ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        char path[MAX_PATH];
        GetSystemDirectoryA(path, MAX_PATH);
        strcat_s(path, "\\dinput8.dll");
        hLibrary = LoadLibraryA(path);
        writePatches();
        break;
    }
    return TRUE;
}
