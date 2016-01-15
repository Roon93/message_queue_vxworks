#include "timer_log.h"

static int TIMER_LOG_LEVEL = 0;

void set_timer_log_level(int level) {
    TIMER_LOG_LEVEL = level;
}

void timer_loginfo(char* fmt, ...) {
    va_list args;
    if (TIMER_LOG_LEVEL > 0) {
        printf("<-timer_loginfo-> ");
        va_start(args,fmt);
        vprintf(fmt,args);
        va_end(args);
        printf("\n"); 
    }
}

void timer_error(char *fmt, ...) {
    va_list args;
    printf("<-timer_error-> ");
    va_start(args,fmt);
    vprintf(fmt,args);
    va_end(args);
    printf("\n");
}

void timer_warning(char* fmt, ...) {
    va_list args;
    if (TIMER_LOG_LEVEL > 1) {
        printf("<-timer_warning-> ");
        va_start(args,fmt);
        vprintf(fmt,args);
        va_end(args);
        printf("\n");
    }
}

void timer_debug(char* fmt, ...) {
    va_list args;
    if (TIMER_LOG_LEVEL > 2) {
        printf("<-timer_debug-> ");
        va_start(args,fmt);
        vprintf(fmt,args);
        va_end(args);
        printf("\n");
    }
}

