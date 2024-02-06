#pragma once
#include "windows.h"

void xi_begin(HINSTANCE hinstance);
void xi_end();

void xi_call_enable(WINBOOL enable);
DWORD xi_call_set_state(DWORD dwIndex, LPVOID lpState);
DWORD xi_call_get_state(DWORD dwIndex, LPVOID lpState);
DWORD WINAPI xi_call_get_keystroke(DWORD dwIndex, DWORD dwReserved, LPVOID lpKeystroke);
DWORD WINAPI xi_call_get_capabilities(DWORD dwIndex, DWORD dwFlags, LPVOID lpCapabilities);
DWORD WINAPI xi_call_get_dsound_audio_device_guids(DWORD dwIndex, GUID* pDSoundRenderGuid, GUID* pDSoundCaptureGuid);
DWORD WINAPI xi_call_get_battery_information(DWORD dwIndex, BYTE devType, LPVOID lpInformation);
DWORD WINAPI xi_call_get_state_ex(DWORD dwIndex, LPVOID lpState);
DWORD WINAPI xi_call_get_audio_device_ids(DWORD dwIndex, LPWSTR lpRenderDeviceId, UINT* lpRenderCount, LPWSTR lpCaptureDeviceId, UINT* lpCaptureCount);
