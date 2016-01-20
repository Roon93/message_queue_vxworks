#include "timer_test.h"

void test_sleep(MSecond ms) {
    timer_loginfo("<--------------------------test sleep------------------------->");
    timer_loginfo("befor sleep %d", ms);
    mySleep(ms);
    timer_loginfo("after sleep %d", ms);
    timer_loginfo("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
}

/* @TODO for vxworks*/
void timeout_callback(long arg0, long arg1, long arg2, long arg3, \
        long arg4, long arg5, long arg6, long arg7, long arg8, long arg9) {
    timer_loginfo("i am the timeout callback");
}
TimerID test_timeout(MSecond ms) {
    timer_loginfo("<----------------------test timeout %d--------------------->", ms);
    return mySetTimeout(ms, timeout_callback, NULL);
}
void test_clear_timeout(TimerID id) {
    timer_loginfo("clear timer timeout %d", id);
    myClearTimeout(id);
}

void interval_callback(long arg0, long arg1, long arg2, long arg3, \
        long arg4, long arg5, long arg6, long arg7, long arg8, long arg9) {
    static int count = 0;
    printf("interval_callback: test");
    count ++;
    timer_loginfo("i am the interval callback %d", count);
}
TimerID test_interval(MSecond ms) {
    timer_loginfo("<-----------------------test interval %d-------------------->", ms);
    return mySetInterval(ms, interval_callback, NULL);
}

void test_clear_interval(TimerID id) {
    timer_loginfo("clear timer interval %d", id);
    myClearInterval(id);
}

int timerTest(int log_level_timer, int log_level_memory) {
    int i = 0; 
    TimerID tmp_id;
    TimerID id[40];
    init_memory_manage(log_level_memory);
    myTimerInit(log_level_timer);
    /* test_sleep(2000);*/
    for (i = 0; i < 20; i ++) {
        tmp_id = test_timeout(1000);
        if (i > 10) {
            test_clear_timeout(tmp_id);
        }
    }
    for (i = 0; i < 20; i ++) {
        id[i] = test_interval(500);
        if (i > 10) {
            test_clear_interval(id[i]);
        }
    }
    mySleep(3000);
    for (i = 0; i <= 10; i ++) {
        test_clear_interval(id[i]);
    }
    mySleep(4000);
    myTimerDeinit();
    deinit_memory_manage();
    return 0;
}
