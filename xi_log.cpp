#include <cstdio>
#include <ctime>
#include "windows.h"

int log_count = 0;

HANDLE log_f = INVALID_HANDLE_VALUE;

void log_begin() {
    if (log_count == 0) {
        //log_f = CreateFile("xi.log", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    }
    log_count++;
}

void log_end() {
    log_count--;
    if (log_count == 0) {
        if (log_f == INVALID_HANDLE_VALUE) { return; }
        CloseHandle(log_f);
    }
}

void log_log(const char* msg) {
    if (log_f == INVALID_HANDLE_VALUE) { return; }

    char buf[512];

    time_t now;
    time(&now);
    strftime(buf, 512, "%Y-%m-%d %H:%M:%S ", gmtime(&now));

    strcat(buf, msg);
    strcat(buf, "\r\n");
    size_t len = strlen(buf);

    WriteFile(log_f, buf, len, NULL, NULL);
}

void log_log_fmt(const char* fmt, ...) {
    if (log_f == INVALID_HANDLE_VALUE) { return; }

    char buf[512];

    va_list lst;
    va_start(lst, fmt);
    int len = vsprintf(buf,fmt, lst);
    va_end( lst );

    log_log(buf);
}
