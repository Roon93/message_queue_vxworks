#include "timer_basic.h"
#include "timer_core.h"

/* Before call the timer you must invoke this function*/
void myTimerInit(int log_level_timer);

/* Before exit the program, you must invoke this function*/
void myTimerDeinit();

/**
 * the sleep timer, which will cause the caller sleep the given time.
 *
 * params:
 *  ms: the millisecond need to sleep.
 * return:
 *  none
 */
void mySleep(MSecond ms);

/**
 * the caller will not be suspend, and the callback function will be called 
 * after the given time elapsed
 *
 * params:
 *  ms: the time before calling the callback function.
 *  callback: the function will be called after the given time
 *  args: the pramameters for the callback function
 * return:
 *  the time id of the timer
 */
TimerID mySetTimeout(MSecond ms, TaskCallback callback, void* args);

/**
 * clear the given timeout timer
 *
 * params:
 *  id: the id of the timeout timer need to be cleard
 * return:
 *  none
 */
void myClearTimeout(TimerID tid);

/**
 * the caller will not be suspend, and the callback will be called with the 
 * given interval until the timer is cleared.
 *
 * params:
 *  ms: the time before calling the callback function.
 *  callback: the function will be called after the given time
 *  args: the pramameters for the callback function
 * return:
 *  the time id of the timer
 */
TimerID mySetInterval(MSecond ms, TaskCallback callback, void* args);

/**
 * clear the given interval timer
 *
 * params:
 *  id: the id of the interval timer need to be cleard
 * return:
 *  none
 */
void myClearInterval(TimerID tid);
