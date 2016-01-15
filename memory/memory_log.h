#include <stdio.h>
#include <stdarg.h>

void set_memory_log_level(int level);

void memory_loginfo(char* fmt, ...);

void memory_error(char* fmt, ...);

void memory_warning(char* fmt, ...);

void memory_debug(char* fmt, ...);
