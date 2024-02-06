#include "windows.h"
#include "xi_log.h"

int guard_count = 0;

const size_t GUARD_SIZE = 8;

LPVOID ref_f1 = nullptr;
LPVOID ref_f2 = nullptr;
byte guard_f1[GUARD_SIZE];
byte guard_f2[GUARD_SIZE];

DWORD WINAPI guard_check(void* data) {
    Sleep(5000);

    byte c_f1[GUARD_SIZE];
    byte c_f2[GUARD_SIZE];

    memcpy(c_f1, ref_f1, GUARD_SIZE);
    memcpy(c_f2, ref_f2, GUARD_SIZE);

    if (memcmp(guard_f1, c_f1, GUARD_SIZE) != 0) {
        log_log("Function XInputGetState is overridden");
        DWORD p_f1;
        if (VirtualProtect(ref_f1, GUARD_SIZE, PAGE_EXECUTE_READWRITE, &p_f1)) {
            memcpy(ref_f1, guard_f1, GUARD_SIZE);
            log_log("Function XInputGetState is restored");
            VirtualProtect(ref_f1, GUARD_SIZE, p_f1, &p_f1);
        } else {
            log_log("Function XInputGetState is NOT restored");
        }
    } else {
        log_log("Function 1 is normal");
    }

    if (memcmp(guard_f2, c_f2, GUARD_SIZE) != 0) {
        log_log("Function XInputGetStateEx is overridden");
        DWORD p_f2;
        if (VirtualProtect(ref_f2, GUARD_SIZE, PAGE_EXECUTE_READWRITE, &p_f2)) {
            memcpy(ref_f2, guard_f2, GUARD_SIZE);
            log_log("Function XInputGetStateEx is restored");
            VirtualProtect(ref_f1, GUARD_SIZE, p_f2, &p_f2);
        } else {
            log_log("Function XInputGetStateEx is NOT restored");
        }
    } else {
        log_log("Function XInputGetStateEx is normal");
    }
    return 0;
}

void guard_begin(LPVOID f1, LPVOID f2) {
    if (guard_count == 0) {
        ref_f1 = f1;
        ref_f2 = f2;
        memcpy(guard_f1, f1, GUARD_SIZE);
        memcpy(guard_f2, f2, GUARD_SIZE);
        CreateThread(NULL, 0, guard_check, NULL, 0, NULL);
    }
    guard_count++;
}

void guard_end() {
    guard_count--;
    if (guard_count == 0) {
    }
}
