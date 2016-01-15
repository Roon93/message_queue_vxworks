#include "mq_basic.h"

MessagePtr createMessage(MessageType type, TaskIDPtr sender, MSecond ttl,\
        MessageInfo description, ContentPtr content);

void insertMessage(MessagePtr msg);

void destroyMessage(MessagePtr msg, int detach_queue);

int compareMessageDescription(MessageInfo msg_desc, MessageInfo other_desc);

int matchMessageReceiver(MessagePtr msg, ReceiverPtr receiver);

void messageTimeoutCallback(long arg0, long arg1, long arg2, long arg3, \
        long arg4, long arg5, long arg6, long arg7, long arg8, long arg9);
