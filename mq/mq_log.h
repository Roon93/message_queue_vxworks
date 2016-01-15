#include <stdio.h>
#include <stdarg.h>

void set_mq_log_level(int level);

void mq_loginfo(char* fmt, ...);

void mq_error(char* fmt, ...);

void mq_warning(char* fmt, ...);

void mq_debug(char* fmt, ...);
