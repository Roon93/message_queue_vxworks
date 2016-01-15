#include <stdio.h>
#include <stdarg.h>

void set_timer_log_level(int level);

void timer_loginfo(char* fmt, ...);

void timer_error(char* fmt, ...);

void timer_warning(char* fmt, ...);

void timer_debug(char* fmt, ...);
