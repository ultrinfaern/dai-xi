#pragma once

void log_begin();
void log_end();

void log_log_fmt(const char* fmt, ...);
void log_log(const char* msg);
