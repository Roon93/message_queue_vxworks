#include "mq_basic.h"

MessagePtr createMessage(MessageType type, TaskIDPtr sender, MSecond ttl,\
        MessageInfo description, ContentPtr content);

void insertMessage(MessagePtr msg);

void destroyMessage(MessagePtr msg, int detach_queue);

int compareMessageDescription(MessageInfo msg_desc, MessageInfo other_desc);

int matchMessageReceiver(MessagePtr msg, ReceiverPtr receiver);

void *messageTimeoutCallback(void* args);
