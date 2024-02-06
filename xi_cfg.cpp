#include <cstdio>
#include "windows.h"

int cfg_count = 0;

bool CFG_LOG = false;
DWORD CFG_TCK_STAGE_1 = 1000;
DWORD CFG_TCK_STAGE_2 = 300;


void cfg_begin() {
    if (cfg_count == 0) {
        HANDLE cfg_f = CreateFile("xi.cfg", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
        if (cfg_f != INVALID_HANDLE_VALUE) {
            DWORD cfg_fs = GetFileSize(cfg_f, NULL);
            char cfg_buf[cfg_fs + 1];
            ReadFile(cfg_f, cfg_buf, cfg_fs, NULL, NULL);
            cfg_buf[cfg_fs] = '\0';
            CloseHandle(cfg_f);

            char* tok = strtok(cfg_buf, "\r\n");
            while (tok != nullptr) {
                if (strncmp(tok, "log=", strlen("log=")) == 0) {
                    char* val = strchr(tok, '=');
                    if (strncmp(val, "=t", strlen("=t")) == 0) {
                        CFG_LOG = true;
                    } else if (strncmp(val, "=f", strlen("=f")) == 0) {
                        CFG_LOG = false;
                    }
                } else if (strncmp(tok, "delay=", strlen("delay=")) == 0) {
                    char *val = strchr(tok, '=');
                    DWORD tck = CFG_TCK_STAGE_1;
                    sscanf(val, "=%lu", &tck);
                    CFG_TCK_STAGE_1 = tck;
                }
                tok = strtok(nullptr, "\r\n");
            }

        }
    }
    cfg_count++;
}

void cfg_end() {
    cfg_count--;
    if (cfg_count == 0) {
    }
}
