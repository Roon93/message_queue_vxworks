#include "timer_basic.h"

void initCallbackInfo();

void deinitCallbackInfo();

TimerID addCallbackItem(TimerItemPtr timer_item, TimerID tid);

void removeCallbackItem(TimerID tid);
