#include "timer_basic.h"
#include "timer_callback.h"

void lockGlobalInfo();
void unlockGlobalInfo();

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

void decreaseTimerNode();
