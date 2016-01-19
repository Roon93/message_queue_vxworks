#include "timer_basic.h"

/* initialize the callback info struct */
void initCallbackInfo();

/* deinitialize the callback info struct*/
void deinitCallbackInfo();

/**
 * add a callback item
 *
 * params: 
 *  timer_item: the correspond timer item of the new callback item
 *  tid: the reused tid, if -1: allocate a new tid, not -1: reuse this tid
 * return:
 *  the tid of the callback item
 */
TimerID addCallbackItem(TimerItemPtr timer_item, TimerID tid);

/**
 * remove the callback item which tid is the given value
 *
 * params:
 *  tid: the callback item need to be removed
 * return:
 *  none
 */
void removeCallbackItem(TimerID tid);
