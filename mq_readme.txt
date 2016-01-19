嵌入式 mq

mq
本部分实现了消息队列，并提供了几种消息队列的使用模式。在实现时，分别使用message队列存储消息，使用receiver队列存储接收接信息。基本模式为，新来的消息对接收者队列进行匹配，如有匹配成功，则消息发送送到相应的接收者，并销毁消息；新到来的接收到对消息队列进行扫描，如有匹配成功则接收对应消息，并销毁消息。本模块提供的消息模式为：常规消息(如果一直没有匹配成功一直待在队列中)，超时消息(如果指定时间没有被接收，则从队列中删除消息)；提供接收者模式为：立即接收(直接扫描消息队列，如果没有匹配成功，则直接返回)，阻塞接收(阻塞调用者，直到超时或者接收到消息)，回调接收(调用者直接返回，在指定的时间内，如果接收到消息则调用回调函数，如果超时，则不再调用回调函数。)
Message: 消息，消息使用desc(描述符)，并且记录其它相关信息，消息内容使用指向堆内存的指针传递，消息内容格式自拟。
消息队列：在消息生成时，如果消息没有匹配成功接收者，则加入消息队列，等待接收者或者基它操作。
Receiver: 接收者，接收者接收的消息类使使用desc(描述符)，只接收desc与其相同的消息，如果没有匹配到消息，且不是立即返回的接收者，则加入接收者队列。

主要文件与函数说明：
mq_basic.h: 消息队列的主要数据结构，以及其它声明。

message_queue.h message_queue.c: mq模块对外接口。
void showMessageQueue():
显示消息队列内容。
void showReceiverQueue()：
显示接收者队列相关内容。
void initMQ(int log_level_mq, int log_level_timer, int log_lever_memory):
初始化mq。
void deinitMQ():
释放mq。
void MQAddNormalMessage(TaskIDPtr id, MessageInfo description, void* data, int data_length):
添加常规消息。
void MQAddTimeoutMessage(TaskIDPtr id, MessageInfo description, void* data, int data_length, MSecond ttl):
添加超时消息。
void MQAddImmediatelyReceiver(TaskIDPtr id, MessageInfo description, ContentPtrPtr contentPtr):
立即接收者。
void MQAddSuspendReceiver(TaskIDPtr id, MessageInfo description, MSecond ttl, ContentPtrPtr contentPtr):
添加阻塞接收者。
void MQAddCallbackReceiver(TaskIDPtr id, MessageInfo description, MSecond ttl, TaskCallback callback):
添加回调接收者。

mq_message.h mq_message.c: 提供消息的相关操作。
MessagePtr createMessage(MessageType type, TaskIDPtr sender, MSecond ttl,MessageInfo description, ContentPtr content):
创建消息。
void insertMessage(MessagePtr msg):
消息队列插入消息。
void destroyMessage(MessagePtr msg, int detach_queue):
从队列中删除消息。
int compareMessageDescription(MessageInfo msg_desc, MessageInfo other_desc):
比对desc(描述符域)。
int matchMessageReceiver(MessagePtr msg, ReceiverPtr receiver):
匹配消息与消息接收者。
void messageTimeoutCallback(long arg0, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6, long arg7, long arg8, long arg9):
消息超时回调函数，主要为从消息队列中删除超时的消息。

mq_receiver.h mq_receiver.c: 提供接收者的相关操作。
ReceiverPtr createReceiver(TaskIDPtr id, MessageInfo desc, MSecond ttl, ReceiverType type, MySemaphorePtr sem, TaskCallback callback, ContentPtrPtr contentPtr):
创收消息接收者。
void insertReceiver(ReceiverPtr receiver):
接收者队列插入消息接收者。
void destroyReceiver(ReceiverPtr receiver, int detach_queue):
从接收者队列中删除消息接收者
void receiverTimeoutCallback(long arg0, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6, long arg7, long arg8, long arg9):
接收者超时回调函数，主要从接收者队列中删除超时的接收者。

mq_queue.h mq_queue.c:
void initMqGlobalInfoLock():
初始化mq全局信息锁。
void lockMqGlobalInfo():
锁住mq全局信息消息。
void unlockMqGlobalInfo():
打开mq全局信息锁。
void addMessage(MessageType type, TaskIDPtr sender, MSecond ttl, MessageInfo description, ContentPtr content):
向消息队列中添加消息。
void addReceiver(TaskIDPtr id, MessageInfo desc, MSecond ttl, ReceiverType type, MySemaphorePtr sem, TaskCallback callback, ContentPtrPtr contentPtr):
向接收者队列中添加接收者。
void processReceiverMessage(MessagePtr msg, ReceiverPtr receiver, int flag):
处理匹配成功的消息与接收者。

mq_log.h mq_log.c: 日志相关。
void set_mq_log_level(int level):
设置日志级别，0:不输出，1:log info信息，2: warning级别，3:debug级别
void mq_loginfo(char* fmt, …):
输入loginfo级别日志。
void mq_warning(char* fmt, …):
输出warning级别日志。
void mq_debug(char* fmt, …):
输出debug级别日志。
void mq_error(char* fmt, …):
输出error日志。

mq_test.h mq_test.c: 相关mq测试。

相关操作：
初始化：初始化mq相关信息，初始timer、memory等，初始化回调信息。
释放：相关数据。
添加消息：添加消息时，首先对接收队列进行扫描，如果匹配成功，则把消息发送到相应的接收者，如果没有接收成功，则把消息加入消息队列。
添加接收者：添加接收者时，首先对消息队列进行扫描，如果匹配成功，则直接接收消息，如果没有，根据消息的类型进行相应操作。




