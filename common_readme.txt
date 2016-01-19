嵌入式   common

common
本模块主要封装了vxworks信号量操作和vxworks task相关操作。

文件与函数简要说明：
common.h: 此模块的头文件

my_process.h my_process.c: task相关操作
int createTask(TaskCallback callback, void* args):
创建新task。

my_semaphore.h my_semaphore.c: 信号量相关操作
MySemaphorePtr initSemaphore():
初始化信号量，并返回信号量句柄。
void waitSemaphore(MySemaphorePtr sem):
等待给定的信号量。
void postSemaphore(MySemaphorePtr sem):
give相应的信号量。
void destroySemaphore(MySemaphorePtr sem):
销毁相应的信号量。

common_log.h common_log.c: 日志相关操作
日志级别，0:不输出，1:log info信息，2: warning级别，3:debug级别
void common_loginfo(char* fmt, …):
输入loginfo级别日志。
void common_warning(char* fmt, …):
输出warning级别日志。
void common_debug(char* fmt, …):
输出debug级别日志。
void common_error(char* fmt, …):
输出error日志。
