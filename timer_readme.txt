嵌入式 timer

timer
实现时，使用一链表记录所有的需要定时的表求，链表中每个结点都有一个时间粒计数，此时间粒计数代表此结点时间数。在运行计时器时，系统递减链表头结点时间粒计数，若是时间粒计数变成0，表示此结点达到定时点，所有定时到这个点的事件都要需要执行预定操作。
本系统实现三种定时器，即sleep, timeout, interval，并提供cancelTimeout, cancelInterval，以下简要介绍相关操作。
sleep：阻塞指定时间。调用此定时器代码会阻塞，直到sleep指定的等待时间到达后，代码才会继续执行。此定时器主要通过信号量实现。
timeout：定触发指定操作。调用此定时器后，代码会继续执行，调用此定时器时，除了需要提供定时时间，还需要提供一个回调函数，此函数将在指定的时间到达时触发。注意：到达预定时间触发的回调函数将在另一个的task中执行。
cancelTimeout：取消指定的timeout定时器，若在timeout触发操作之前调用此功能，取消后相关的timeout定时器不会再触发。
interval：间隔指定时间不断触发指定操作。调用此定时器后，代码会继续执行，调用此定时器时，需要提供定时时间和回调函数，与timeout操作不同的是，此定时器间隔指定时间，不断触发指定操作。
cancelTimeout: 取消指定的interval定时器。从此操作开始，之后相应的interval操作将不再触发。
实现相关概念介绍
TimerNode：时间结点，每一个时间结点都有一个时间粒属性，表示本结点占用时间长度。时间粒大于1的时间结点，还可以进行分裂，分裂成两个更小的结点。
时间链： 时间结点链表，每次接收到系统触发时，都会对链表头结点进行递减操作，若时头结点递减到0，则会触发预定操作，并删除此结点。在添加定时，会找到或者新增相应的时间结点。
TimerItem：时间项，每个时间结点可能会有0个或多个预定操作，每个时间项便是记录相关操作，在到达指定时间结点时，系统会执行所有相应的预定操作。
Callback空闲结点：空闲回调结点，当插入timeout或者interval定时器时，系统会申请一个空闲回调结点，从本结点返回一个tid，tid便是此定时器的编号。
CallbackInfo信息：用于存储回调式定时器相关信息的节点，提信Callback空闲链和回调槽。回调槽只有有限个，使用数组存储，这样可以保证最快速查找到tid对应的定时器。

主要文件及函数简要说明：
timer_basic.h：本文件为timer模块相关数据结构，以及基它辅助声明。

timer.h timer.c: 此文件向外提供timer模块相关api等。
void myTimerInit(int log_level_timer, int log_level_memory):
初始化timer模块以及其它相关前提，两个参数分别指定了timer与memory的日志级别，在使用timer模块前必须先调用此模块。
void myTimerDeinit():
释放timer模块相关信息。
void mySleep(MSecond ms):
阻塞指定时间。
TimerID mySetTimeout(MSecond ms, TaskCallback callback, void* args):
添加超时回调定时器。
void myClearTimeout(TimerID tid):
删除指定的超时回调定时器。
TimerID mySetInterval(MSecond ms, TaskCallback callback, void* args):
添加间隔重复调用定时器。
void myClearInterval(TimerID tid):
删除批定的间隔重复调用定时器。

timer_core.h timer_core.c: 提供定时器相关核心操作。
void initTimerGlobalLock():
初始化全局信息锁。
void lockTimerGlobalInfo():
开启全局信息锁。
void unlockTimerGlobalInfo():
释放全局信息锁。
void initTimer():
进行定时器初始化。
TimerID insertTimerItem(int tick_num, TimerItemType type, MySemaphorePtr sem, TaskCallback callback, void* args, TimerID tid):
插入定时项。
void removeTimerItem(TimerItemPtr ptr):
移除定时项。
void activateTimerItem(TimerItemPtr ptr):
激活定时项相关操作。
TimerNodePtr insertTimerNode(TimerNodePtr end, int tick_num):
插入时间结点。
TimerNodePtr splitTimerNode(TimerNodePtr cur, int tick_num):
分割时间结点。
void removeTimerNode(TimerNodePtr ptr):
移除时间结点。
void decreaseTimerNode(long arg0, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6, long arg7, long arg8, long arg9):
时间结点链操作函数，timer初始化时开启此函数，每次接收到系统时钟跳动时操作时间结点链头结点，并在头结点为0时，激活相应的时间项。

timer_callback.h timer_callback.c: 回调相关操作。
void initCallbackInfo():
初始化回调相关数据。
void deinitCallbackInfo():
释放回调相关数据。
TimerID addCallbackItem(TimerItemPtr timer_item, TimerID tid):
添加回调信息，若tid不为不为-1，则对应位置为回调块，否则系统分配。
void removeCallbackItem(TimerID tid):
删除回调信息。

timer_log.h timer_log.c: 日志相磁操作
void set_timer_log_level(int level):
设置日志级别，0:不输出，1:log info信息，2: warning级别，3:debug级别
void timer_loginfo(char* fmt, …):
输入loginfo级别日志。
void timer_warning(char* fmt, …):
输出warning级别日志。
void timer_debug(char* fmt, …):
输出debug级别日志。
void timer_error(char* fmt, …):
输出error日志。

timer_test.h timer_test.c: 提供相关测试代码

相关操作：
初始化：主要初始化memory模块(本模块使用memory模块分配内存)，时间结点链相关信息，回调信息，以及相关锁等。
释放信息：释放分配的相关数据，信息。
添加定时器：定时器分为sleep，timeout，interval三种类别，不同的类别提供需要提供不同的信息，但是定时操作都是相同的，只是其预定操作有所不同。添加定时器时，首先找到对应的时间结点，这个结点可能直找到，可能需要添加，也可能需要分裂现有结点，然后在时间结点上添加相定的定时项。
删除定时器：对于timeout，interval两种类别定时间可以进行删操作，在删除时需要提供对就原tid，tid可以快速找到回调信息，并使用其中指定时项的指针进行去定时操作。
时钟推进：在每次接收到系统时钟后，都会操作时间链头结点，并进行时间粒计数递减，若时间粒计数变为0，则进行相关的定时项操作。




