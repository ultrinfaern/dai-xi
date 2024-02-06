#include "windows.h"
#include "xi_cfg.h"
#include "xi_log.h"
#include "xi_xi.h"
#include "xi_fun.h"
#include "xi_guard.h"

extern "C" __declspec( dllexport ) void WINAPI XInputEnable(WINBOOL enable) {
    xi_call_enable(enable);
}

extern "C" __declspec( dllexport ) DWORD WINAPI XInputSetState(DWORD dwIndex, LPVOID lpVibration) {
    return xi_call_set_state(dwIndex, lpVibration);
}

extern "C" __declspec( dllexport ) DWORD WINAPI XInputGetState(DWORD dwIndex, LPVOID lpState) {
    return xi_fun_get_state(dwIndex, lpState);
}

extern "C" __declspec( dllexport ) DWORD WINAPI XInputGetKeystroke(DWORD dwIndex, DWORD dwReserved, LPVOID lpKeystroke) {
    return xi_call_get_keystroke(dwIndex, dwReserved, lpKeystroke);
}

extern "C" __declspec( dllexport ) DWORD WINAPI XInputGetCapabilities(DWORD dwIndex, DWORD dwFlags,LPVOID lpCapabilities) {
    return xi_call_get_capabilities(dwIndex, dwFlags, lpCapabilities);
}

extern "C" __declspec( dllexport ) DWORD WINAPI XInputGetDSoundAudioDeviceGuids(DWORD dwIndex, GUID* lpDSoundRenderGuid, GUID* lpDSoundCaptureGuid) {
    return xi_call_get_dsound_audio_device_guids(dwIndex, lpDSoundRenderGuid, lpDSoundCaptureGuid);
}

extern "C" __declspec( dllexport ) DWORD WINAPI XInputGetBatteryInformation(DWORD dwIndex, BYTE devType, LPVOID lpInformation) {
    return xi_call_get_battery_information(dwIndex, devType, lpInformation);
}

extern "C" __declspec( dllexport ) DWORD WINAPI XInputGetStateEx(DWORD dwIndex, LPVOID lpState) {
    return xi_fun_get_state_ex(dwIndex, lpState);
}

extern "C" __declspec( dllexport ) DWORD WINAPI XInputGetAudioDeviceIds(DWORD dwIndex, LPWSTR lpRenderDeviceId, UINT* lpRenderCount, LPWSTR lpCaptureDeviceId, UINT* lpCaptureCount) {
    return xi_call_get_audio_device_ids(dwIndex, lpRenderDeviceId, lpRenderCount, lpCaptureDeviceId, lpCaptureCount);
}

extern "C" __declspec( dllexport ) BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            cfg_begin();
            log_begin();
            xi_begin(hinstDLL);
            guard_begin((LPVOID) XInputGetState, (LPVOID) XInputGetStateEx);
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
        case DLL_PROCESS_DETACH:
            guard_end();
            xi_end();
            log_end();
            cfg_end();
            break;
        default:
            break;
    }
    return TRUE;
}
