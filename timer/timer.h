#include "timer_basic.h"
#include "timer_core.h"

/* Before call the timer you must invoke this function*/
void myTimerInit(int log_level_timer, int log_level_memory);

/* Before exit the program, you must invoke this function*/
void myTimerDeinit();

void mySleep(MSecond ms);

TimerID mySetTimeout(MSecond ms, TaskCallback callback, void* args);

void myClearTimeout(TimerID tid);

TimerID mySetInterval(MSecond ms, TaskCallback callback, void* args);

void myClearInterval(TimerID tid);
