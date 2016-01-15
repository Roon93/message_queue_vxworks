#include "timer.h"

MySemaphorePtr g_timer_chain_sem = NULL;
MySemaphorePtr g_timer_callback_info_sem = NULL;

/* Before call the timer you must invoke this function*/
void myTimerInit(int log_level_timer, int log_level_memory) {
    g_timer_chain_sem = initSemaphore();
    postSemaphore(g_timer_chain_sem);
    g_timer_callback_info_sem = initSemaphore();
    postSemaphore(g_timer_callback_info_sem);

    init_memory_manage(log_level_memory);
    set_timer_log_level(log_level_timer);
    initTimer();
    timer_loginfo("init success");
}

/* Before exit the program, you must invoke this function*/
void myTimerDeinit() {
    deinitTimer();
    deinit_memory_manage();
    timer_loginfo("init deinit success");
}

int mSecondToTick(MSecond ms) {
    return (ms - 1) / TICK + 1;
}

void mySleep(MSecond ms) {
    MySemaphorePtr sem;
    timer_loginfo("befor sleep");
    sem = initSemaphore();
    timer_loginfo("sleep %d ms, %d tick", ms, mSecondToTick(ms));
    insertTimerItem(mSecondToTick(ms), TIMER_SEM, sem, NULL, NULL, -1);
    waitSemaphore(sem);
    destroySemaphore(sem);
    timer_loginfo("after sleep");
}

TimerID mySetTimeout(MSecond ms, TaskCallback callback, void* args) {
    TimerID tid;
    timer_loginfo("set timeout %d ms, %d tick", ms, mSecondToTick(ms));
    tid = insertTimerItem(mSecondToTick(ms), TIMER_TIMEOUT, NULL, callback, args, -1);
    return tid;
}

void myClearTimeout(TimerID tid) {
    if (g_timer_callback_info->items[tid] != NULL) {
        removeTimerItem(g_timer_callback_info->items[tid]);
    }
    removeCallbackItem(tid);
    timer_loginfo("clear timeout success");
}

TimerID mySetInterval(MSecond ms, TaskCallback callback, void* args) {
    TimerID tid;
    timer_loginfo("set interval %d ms", ms);
    timer_debug("mySetInterval: g_timer_callback_info %d", g_timer_callback_info);
    tid = insertTimerItem(mSecondToTick(ms), TIMER_INTERVAL, NULL, callback, args,\
            -1);
    return tid;
}

void myClearInterval(TimerID tid) {
    timer_debug("myClearInterval: tid %d, %d", tid, g_timer_callback_info);
    if (g_timer_callback_info == NULL) {
        timer_debug("myClearInterval: null");
    }
    if (g_timer_callback_info->items[tid] != NULL) {
        timer_debug("myClearTimeout: valid clear");
        removeTimerItem(g_timer_callback_info->items[tid]);
    }
    timer_debug("myClearInterval: remove callback");
    removeCallbackItem(tid);
    timer_loginfo("clear timeout success");
}

