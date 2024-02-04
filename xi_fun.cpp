#include "windows.h"
#include "xinput.h"
#include "xi_log.h"
#include "xi_xi.h"

enum XI_STAGE { OFF, ON_STAGE_0, ON_STAGE_1, ON_STAGE_2, ON_STAGE_3 };
const DWORD TCK_STAGE_1 = 1000;
const DWORD TCK_STAGE_2 = 500;

enum XI_STAGE xi_fun_stage = OFF;
DWORD xi_fun_pn_delta = 0;
DWORD xi_fun_tck_stage_1;
DWORD xi_fun_tck_stage_2;

void xi_fun_alter(PXINPUT_STATE lpState) {
    DWORD pn = lpState->dwPacketNumber;
    bool pressed = (lpState->Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0;
    log_log_fmt("Call fun state (%d) - (%d) - (%d)", pn, pressed, xi_fun_stage);

    DWORD tck_now = GetTickCount();
    if (pressed) {
        if (xi_fun_stage == OFF) {
            xi_fun_stage = ON_STAGE_0;
        }
        if (xi_fun_stage == ON_STAGE_1) {
            xi_fun_stage = ON_STAGE_3;
        }
        if (xi_fun_stage == ON_STAGE_2) {
            xi_fun_stage = ON_STAGE_3;
        }
    } else {
        if (xi_fun_stage == ON_STAGE_0) {
            xi_fun_stage = ON_STAGE_1;
            xi_fun_tck_stage_1 = tck_now;
        }
        if (xi_fun_stage == ON_STAGE_1) {
            DWORD tck_delta = tck_now - xi_fun_tck_stage_1;
            if (tck_delta >= TCK_STAGE_1) {
                xi_fun_stage = ON_STAGE_2;
                xi_fun_tck_stage_2 = tck_now;
                xi_fun_pn_delta = xi_fun_pn_delta + 1;
            }
        }
        if (xi_fun_stage == ON_STAGE_2) {
            DWORD tck_delta = tck_now - xi_fun_tck_stage_2;
            if (tck_delta < TCK_STAGE_2) {
                lpState->Gamepad.wButtons = lpState->Gamepad.wButtons | XINPUT_GAMEPAD_LEFT_THUMB;
            } else {
                xi_fun_stage = ON_STAGE_1;
                xi_fun_tck_stage_1 = tck_now;
                xi_fun_pn_delta = xi_fun_pn_delta + 1;
            }
        }
        if (xi_fun_stage == ON_STAGE_3) {
            xi_fun_stage = OFF;
        }
    }

    lpState->dwPacketNumber = lpState->dwPacketNumber + xi_fun_stage;
}

DWORD xi_fun_get_state(DWORD dwIndex, LPVOID lpState) {
    DWORD result = xi_call_get_state(dwIndex, lpState);
    xi_fun_alter((PXINPUT_STATE) lpState);
    return result;
}

DWORD WINAPI xi_fun_get_state_ex(DWORD dwIndex, LPVOID lpState) {
    DWORD result = xi_call_get_state_ex(dwIndex, lpState);
    xi_fun_alter((PXINPUT_STATE) lpState);
    return result;
}
