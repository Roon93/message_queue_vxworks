#include "mq_basic.h"
#include "mq_message.h"
#include "mq_receiver.h"

void addMessage(MessageType type, TaskIDPtr sender, MSecond ttl, \
        MessageInfo description, ContentPtr content);

void addReceiver(TaskIDPtr id, MessageInfo desc, MSecond ttl, \
        ReceiverType type, MySemaphorePtr sem, TaskCallback callback, \
        ContentPtrPtr contentPtr);

void processReceiverMessage(MessagePtr msg, ReceiverPtr receiver, int flag);


