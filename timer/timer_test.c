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
    return NULL;
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
    printf("interval_callback: test");
    static int count = 0;
    count ++;
    timer_loginfo("i am the interval callback %d", count);
    return NULL;
}
TimerID test_interval(MSecond ms) {
    timer_loginfo("<-----------------------test interval %d-------------------->", ms);
    return mySetInterval(ms, interval_callback, NULL);
}

void test_clear_interval(TimerID id) {
    timer_loginfo("clear timer interval %d", id);
    myClearInterval(id);
}

int main(int argc, char* argv[]) {
    int log_level_timer = 0;
    int log_level_memory = 0;
    if (argc >= 2) {
        log_level_timer = atoi(argv[1]);
    }
    if (argc >= 3) {
        log_level_memory = atoi(argv[2]);
    }
    myTimerInit(log_level_timer, log_level_memory);
    /* test_sleep(2000);*/
    test_sleep(4000);
    /* test_timeout(3000);*/
    /* test_timeout(3000);*/
    /* TimerID timeout_id = test_timeout(5000);*/
    /* myClearTimeout(timeout_id);*/
    /* TimerID interval_id = test_interval(3000);*/
    /* TimerID interval_id1 = test_interval(5000);*/
    /* sleep(20);*/
    /* test_clear_interval(interval_id);*/
    /* sleep(20);*/
    /* test_clear_timeout(interval_id1);*/
    sleep(10);
    myTimerDeinit();
    return 0;
}
