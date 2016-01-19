#include "timer_basic.h"
#include "timer_callback.h"

void initTimerGlobalLock();

void lockTimerGlobalInfo();

void unlockTimerGlobalInfo();

void destroyTimerGlobalInfo();

void initTimer();

void deinitTimer();

TimerID insertTimerItem(int tick_num, TimerItemType type, MySemaphorePtr sem, \
        TaskCallback callback, void* args, TimerID tid);

void removeTimerItem(TimerItemPtr ptr);

void activateTimerItem(TimerItemPtr ptr);

TimerNodePtr findTimerNode(int tick_num);

TimerNodePtr insertTimerNode(TimerNodePtr end, int tick_num);

TimerNodePtr splitTimerNode(TimerNodePtr cur, int tick_num);

void removeTimerNode(TimerNodePtr ptr);

void decreaseTimerNode(long arg0, long arg1, long arg2, long arg3, long arg4, \
                long arg5, long arg6, long arg7, long arg8, long arg9);
