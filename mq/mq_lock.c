#include "mq_lock.h"
MySemaphorePtr g_mq_global_info_sem = NULL;

void initMqGlobalInfoLock() {
    g_mq_global_info_sem = initSemaphore();
    postSemaphore(g_mq_global_info_sem);
}

void lockMqGlobalInfo() {
    waitSemaphore(g_mq_global_info_sem);
}

void unlockMqGlobalInfo() {
    postSemaphore(g_mq_global_info_sem);
}

void deinitMqGlobalInfoLock() {
    destroySemaphore(g_mq_global_info_sem);
}
