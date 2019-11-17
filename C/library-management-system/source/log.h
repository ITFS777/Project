#pragma once
#define LOG 1
#define LOG_FILENAME "log.txt"
char* get_time(void);
void log_datebase_add(const struct bookinf* p);
void log_datebase_del(const struct bookinf* p);
void log_datebase_save(void);
void log_datebase_load(void);
void log_system_open(void);
void log_system_close(void);