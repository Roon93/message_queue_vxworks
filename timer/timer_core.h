#include "timer_basic.h"
#include "timer_callback.h"

/* init the global information lock*/
void initTimerGlobalLock();

/* lock the global information*/
void lockTimerGlobalInfo();

/* unlock the global information*/
void unlockTimerGlobalInfo();

/* destroy the global information lock*/
void destroyTimerGlobalInfo();

/* init the timer*/
void initTimer();

/* deinit the timer*/
void deinitTimer();

/**
 * insert a timer item according to given information
 *
 * params:
 *  tick_num: the tick number of this timer item
 *  type: the type of the timer item
 *  sem: the semaphore for sleep type timer item
 *  callback: the callback function for the callback timer item
 *  args: the args for the callback function
 *  tid: the reuse tid of the timer item
 * return:
 *  the tid of the timer item
 */
TimerID insertTimerItem(int tick_num, TimerItemType type, MySemaphorePtr sem, \
        TaskCallback callback, void* args, TimerID tid);

/* remove a timer item with the given tid*/
void removeTimerItem(TimerItemPtr ptr);

/* activate a timer item*/
void activateTimerItem(TimerItemPtr ptr);

/* find the correspond timer node for the given tick num*/
TimerNodePtr findTimerNode(int tick_num);

/* insert a timer node into the timer node chain, with the given tick_num*/
TimerNodePtr insertTimerNode(TimerNodePtr end, int tick_num);

/**
 * split the timer node with a subnode with tick number is tick_num
 *
 * params:
 *  cur: the timer node need to be split
 *  tick_num: the tick number of the sub node
 * return:
 *  the splited sub timer node
 */
TimerNodePtr splitTimerNode(TimerNodePtr cur, int tick_num);

/* remove a timer node*/
void removeTimerNode(TimerNodePtr ptr);

/* decrease the tick number of the timer node when received a system tick,
 * we use a semaphore to synchrony with the system tick interruption*/
void decreaseTimerNode(long arg0, long arg1, long arg2, long arg3, long arg4, \
                long arg5, long arg6, long arg7, long arg8, long arg9);
