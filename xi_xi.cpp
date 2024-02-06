#include <string>
#include "windows.h"
#include <shfolder.h>
#include <shlobj.h>
#include "xinput.h"
#include "xi_cfg.h"
#include "xi_log.h"

typedef void WINAPI (*XI_ENABLE)(WINBOOL);
typedef DWORD WINAPI (*XI_SET_STATE)(DWORD, PXINPUT_VIBRATION);
typedef DWORD WINAPI (*XI_GET_STATE)(DWORD, PXINPUT_STATE);
typedef DWORD WINAPI (*XI_GET_KEYSTROKE)(DWORD, DWORD, PXINPUT_KEYSTROKE);
typedef DWORD WINAPI (*XI_GET_CAPABILITIES)(DWORD, DWORD, PXINPUT_CAPABILITIES);
typedef DWORD WINAPI (*XI_GET_DSOUND_AUDIO_DEVICE_GUIDS)(DWORD, GUID*, GUID*);
typedef DWORD WINAPI (*XI_GET_BATTERY_INFORMATION)(DWORD, BYTE, PXINPUT_BATTERY_INFORMATION);
typedef DWORD WINAPI (*XI_GET_STATE_EX)(DWORD, PXINPUT_STATE);
typedef DWORD WINAPI (*XI_GET_AUDIO_DEVICE_IDS)(DWORD, LPWSTR, UINT*, LPWSTR, UINT*);

int xi_count = 0;

HMODULE xi_library;
XI_ENABLE xi_enable;
XI_SET_STATE xi_set_state;
XI_GET_STATE xi_get_state;
XI_GET_KEYSTROKE  xi_get_keystroke;
XI_GET_CAPABILITIES xi_get_capabilities;
XI_GET_DSOUND_AUDIO_DEVICE_GUIDS xi_get_dsound_audio_device_guids;
XI_GET_BATTERY_INFORMATION xi_get_battery_information;
XI_GET_STATE_EX xi_get_state_ex;
XI_GET_AUDIO_DEVICE_IDS xi_get_audio_device_ids;

void xi_stub_enable(WINBOOL enable) {
}

DWORD xi_stub_set_state(DWORD dwIndex, PXINPUT_VIBRATION lpState) {
    return ERROR_DEVICE_NOT_CONNECTED;
}

DWORD xi_stub_get_state(DWORD dwIndex, PXINPUT_STATE lpState) {
    return ERROR_DEVICE_NOT_CONNECTED;
}

DWORD WINAPI xi_stub_get_keystroke(DWORD dwIndex, DWORD dwReserved, PXINPUT_KEYSTROKE lpKeystroke) {
    return ERROR_DEVICE_NOT_CONNECTED;
}

DWORD WINAPI xi_stub_get_capabilities(DWORD dwIndex, DWORD dwFlags, PXINPUT_CAPABILITIES lpCapabilities) {
    return ERROR_DEVICE_NOT_CONNECTED;
}

DWORD WINAPI xi_stub_get_dsound_audio_device_guids(DWORD dwIndex, GUID* lpDSoundRenderGuid, GUID* lpDSoundCaptureGuid) {
    return ERROR_DEVICE_NOT_CONNECTED;
}

DWORD WINAPI xi_stub_get_battery_information(DWORD dwIndex, BYTE devType, PXINPUT_BATTERY_INFORMATION lpInformation) {
    return ERROR_DEVICE_NOT_CONNECTED;
}

DWORD WINAPI xi_stub_get_state_ex(DWORD dwIndex, PXINPUT_STATE lpState) {
    return ERROR_DEVICE_NOT_CONNECTED;
}

DWORD WINAPI xi_stub_get_audio_device_ids(DWORD dwIndex, LPWSTR lpRenderDeviceId, UINT* lpRenderCount, LPWSTR lpCaptureDeviceId, UINT* lpCaptureCount) {
    return ERROR_DEVICE_NOT_CONNECTED;
}

void xi_begin(HINSTANCE hinstance) {
    TCHAR pmn[MAX_PATH];
    TCHAR pln[MAX_PATH];

    GetModuleFileName(hinstance, pmn, MAX_PATH);
    log_log_fmt("Module name is %s", pmn);
    if (FAILED(SHGetFolderPath(NULL, CSIDL_SYSTEM, NULL, SHGFP_TYPE_CURRENT, pln))) {
        strcpy(pln, TEXT("C:\\WINDOWS\\SYSTEM32"));
    }
    log_log_fmt("System folder is %s", pln);

    TCHAR* pxn = strrchr(pmn, '\\');
    strcat(pln, pxn);
    log_log_fmt("Library name is %s", pln);

    if (xi_count == 0) {
        xi_library = LoadLibrary(pln);
        if (xi_library != NULL) {
            log_log("Library loaded");
            //
            xi_enable = (XI_ENABLE) GetProcAddress(xi_library, "XInputEnable");
            if (xi_enable != NULL) {
                log_log("Function XInputEnable imported");
            } else {
                xi_enable = (XI_ENABLE) xi_stub_enable;
                log_log("Function XInputEnable NOT imported");
            }
            //
            xi_set_state = (XI_SET_STATE) GetProcAddress(xi_library, "XInputSetState");
            if (xi_set_state != NULL) {
                log_log("Function XInputSetState imported");
            } else {
                xi_set_state = xi_stub_set_state;
                log_log("Function XInputSetState NOT imported");
            }
            //
            xi_get_state = (XI_GET_STATE) GetProcAddress(xi_library, "XInputGetState");
            if (xi_get_state != NULL) {
                log_log("Function XInputGetState imported");
            } else {
                xi_get_state = xi_stub_get_state;
                log_log("Function XInputGetState NOT imported");
            }
            //
            xi_get_keystroke = (XI_GET_KEYSTROKE) GetProcAddress(xi_library, "XInputGetKeystroke");
            if (xi_get_keystroke != NULL) {
                log_log("Function XInputGetKeystroke imported");
            } else {
                xi_get_keystroke = xi_stub_get_keystroke;
                log_log("Function XInputGetKeystroke NOT imported");
            }
            //
            xi_get_capabilities = (XI_GET_CAPABILITIES) GetProcAddress(xi_library, "XInputGetCapabilities");
            if (xi_get_capabilities != NULL) {
                log_log("Function XInputGetCapabilities imported");
            } else {
                xi_get_capabilities = xi_stub_get_capabilities;
                log_log("Function XInputGetCapabilities NOT imported");
            }
            //
            xi_get_dsound_audio_device_guids = (XI_GET_DSOUND_AUDIO_DEVICE_GUIDS) GetProcAddress(xi_library, "XInputGetDSoundAudioDeviceGuids");
            if (xi_get_dsound_audio_device_guids != NULL) {
                log_log("Function XInputGetDSoundAudioDeviceGuids imported");
            } else {
                xi_get_dsound_audio_device_guids = xi_stub_get_dsound_audio_device_guids;
                log_log("Function XInputGetDSoundAudioDeviceGuids NOT imported");
            }
            //
            xi_get_battery_information = (XI_GET_BATTERY_INFORMATION) GetProcAddress(xi_library, "XInputGetBatteryInformation");
            if (xi_get_battery_information != NULL) {
                log_log("Function XInputGetBatteryInformation imported");
            } else {
                xi_get_battery_information = xi_stub_get_battery_information;
                log_log("Function XInputGetBatteryInformation NOT imported");
            }
            //
            xi_get_state_ex = (XI_GET_STATE_EX) GetProcAddress(xi_library, "XInputGetStateEx");
            if (xi_get_state_ex != NULL) {
                log_log("Function XInputGetStateEx imported");
            } else {
                xi_get_state_ex = xi_stub_get_state_ex;
                log_log("Function XInputGetStateEx NOT imported");
            }
            //
            xi_get_audio_device_ids = (XI_GET_AUDIO_DEVICE_IDS) GetProcAddress(xi_library, "XInputGetAudioDeviceIds");
            if (xi_get_audio_device_ids != NULL) {
                log_log("Function XInputGetAudioDeviceIds imported");
            } else {
                xi_get_audio_device_ids = xi_stub_get_audio_device_ids;
                log_log("Function XInputGetAudioDeviceIds NOT imported");
            }
        } else {
            log_log("Library NOT loaded");
            xi_enable = xi_stub_enable;
            xi_set_state = xi_stub_set_state;
            xi_get_state = xi_stub_get_state;
            xi_get_keystroke = xi_stub_get_keystroke;
            xi_get_capabilities = xi_stub_get_capabilities;
            xi_get_dsound_audio_device_guids = xi_stub_get_dsound_audio_device_guids;
            xi_get_battery_information = xi_stub_get_battery_information;
            xi_get_state_ex = xi_stub_get_state_ex;
            xi_get_audio_device_ids = xi_stub_get_audio_device_ids;
        }
        log_log_fmt("Delay 1 is %ul", CFG_TCK_STAGE_1);
        log_log_fmt("Delay 2 is %ul", CFG_TCK_STAGE_2);
    }
    xi_count++;
}

void xi_end() {
    xi_count--;
    if (xi_count == 0) {
        xi_enable = nullptr;
        FreeLibrary(xi_library);
        log_log("Library unloaded");
    }
}


void xi_call_enable(WINBOOL enable) {
    (*xi_enable)(enable);
}

DWORD xi_call_set_state(DWORD dwIndex, LPVOID lpState) {
    return (*xi_set_state)(dwIndex, (PXINPUT_VIBRATION) lpState);
}

DWORD xi_call_get_state(DWORD dwIndex, LPVOID lpState) {
    return (*xi_get_state)(dwIndex, (PXINPUT_STATE) lpState);
}

DWORD WINAPI xi_call_get_keystroke(DWORD dwIndex, DWORD dwReserved, LPVOID lpKeystroke) {
    return (*xi_get_keystroke)(dwIndex, dwReserved, (PXINPUT_KEYSTROKE) lpKeystroke);
}

DWORD WINAPI xi_call_get_capabilities(DWORD dwIndex, DWORD dwFlags, LPVOID lpCapabilities) {
    return (*xi_get_capabilities)(dwIndex, dwFlags, (PXINPUT_CAPABILITIES) lpCapabilities);
}

DWORD WINAPI xi_call_get_dsound_audio_device_guids(DWORD dwIndex, GUID* lpDSoundRenderGuid, GUID* lpDSoundCaptureGuid) {
    return (*xi_get_dsound_audio_device_guids)(dwIndex, lpDSoundRenderGuid, lpDSoundCaptureGuid);
}

DWORD WINAPI xi_call_get_battery_information(DWORD dwIndex, BYTE devType, LPVOID lpInformation) {
    return (*xi_get_battery_information)(dwIndex, devType, (PXINPUT_BATTERY_INFORMATION) lpInformation);
}

DWORD WINAPI xi_call_get_state_ex(DWORD dwIndex, LPVOID lpState) {
    return (*xi_get_state_ex)(dwIndex, (PXINPUT_STATE) lpState);
}

DWORD WINAPI xi_call_get_audio_device_ids(DWORD dwIndex, LPWSTR lpRenderDeviceId, UINT* lpRenderCount, LPWSTR lpCaptureDeviceId, UINT* lpCaptureCount) {
    return (*xi_get_audio_device_ids)(dwIndex, lpRenderDeviceId, lpRenderCount, lpCaptureDeviceId, lpCaptureCount);
}
