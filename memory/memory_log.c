#include "memory_log.h"

static int MEMORY_LOG_LEVEL = 0;

void set_memory_log_level(int level) {
    MEMORY_LOG_LEVEL = level;
}
void memory_loginfo(char* fmt, ...) {
    va_list args;
    if (MEMORY_LOG_LEVEL > 0) {
        printf("<-memory_loginfo-> ");
        va_start(args,fmt);
        vprintf(fmt,args);
        va_end(args);
        printf("\n"); 
    }
}

void memory_error(char *fmt, ...) {
    va_list args;
    printf("<-memory_error-> ");
    va_start(args,fmt);
    vprintf(fmt,args);
    va_end(args);
    printf("\n");
}

void memory_warning(char* fmt, ...) {
    va_list args;
    if (MEMORY_LOG_LEVEL > 1) {
        printf("<-memory_warning-> ");
        va_start(args,fmt);
        vprintf(fmt,args);
        va_end(args);
        printf("\n");
    }
}

void memory_debug(char* fmt, ...) {
    va_list args;
    if (MEMORY_LOG_LEVEL > 2) {
        printf("<-memory_debug-> ");
        va_start(args,fmt);
        vprintf(fmt,args);
        va_end(args);
        printf("\n");
    }
}

