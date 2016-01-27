#include "timer_test.h"

void timer_test_case_1() {
    MSecond ms = 3000;
    printf("**************test sleep**************\n");
    printf("befor sleep %d\n", ms);
    mySleep(ms);
    printf("after sleep %d\n", ms);
    printf("**************************************\n\n");
}

void timeout_callback(int arg0, int arg1, int arg2, int arg3, int arg4, \
        int arg5, int arg6, int arg7, int arg8, int arg9) {
    printf("@@@i am the timeout callback %d\n", arg0);
}
void timer_test_case_2() {
    TimerID id;
    int count = 0;
    printf("**************test timeout*****************\n");
    for (count = 0; count < 20; count ++) {
        id = mySetTimeout(3000, timeout_callback, count);
        mySleep(500);
        if (count > 10) {
            myClearTimeout(id);
        }
    }
    mySleep(5000);
    printf("*******************************************\n\n");
}

void interval_callback(int arg0, int arg1, int arg2, int arg3, int arg4, \
        int arg5, int arg6, int arg7, int arg8, int arg9) {
    printf(">>>i am the interval callback %d\n", arg0);
}
void timer_test_case_3() {
    int count = 0;
    TimerID tid[10];
    printf("**************test interval*****************\n");
    for (count = 0; count < 10; count ++) {
        tid[count] = mySetInterval(3000, interval_callback, count);
        mySleep(500);
    }
    mySleep(10000);
    printf("\n*************test clear interval****************\n");
    for (count = 0; count < 10; count ++) {
        myClearInterval(tid[count]);
    }
    printf("*******************************************\n\n");
}

int timerTest(int log_level_timer, int log_level_memory) {
    init_memory_manage(log_level_memory);
    myTimerInit(log_level_timer);

    timer_test_case_1();
    timer_test_case_2();
    timer_test_case_3();

    myTimerDeinit();
    deinit_memory_manage();
    return 0;
}
