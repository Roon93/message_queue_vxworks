#include "mq_basic.h"

/* initialize the message queue global info*/
void initMqGlobalInfoLock();

/* lock message queue related global info*/
void lockMqGlobalInfo();

/* unlock message queue related global info*/
void unlockMqGlobalInfo();

/* release message queue related global info*/
void deinitMqGlobalInfoLock();
