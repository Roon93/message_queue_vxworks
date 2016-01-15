#include "message_queue.h"

MessagePtr g_mq_message_queue = NULL;
ReceiverPtr g_mq_receiver_queue = NULL;

void showMessageQueue() {
    MessagePtr msg = g_mq_message_queue;
    printf("the current Message queue\n");
    while (msg != NULL) {
        printf("----%s----\n", msg->desc);
        msg = msg->next;
    }
}

void showReceiverQueue() {
    ReceiverPtr ptr = g_mq_receiver_queue;
    printf("the current Receiver queue\n");
    while (ptr != NULL) {
        printf("****%s****\n", ptr->desc);
        ptr = ptr->next;
    }
}

void initMQ(int log_level_mq, int log_level_timer, int log_lever_memory) {
    mq_loginfo("begin init mq");
    set_mq_log_level(log_level_mq);
    myTimerInit(log_level_timer, log_lever_memory);
    mq_loginfo("success init mq");
}

void deinitMQ() {
    mq_loginfo("begin deinit mq");
    mq_loginfo("begin deinit message queue");
    while (g_mq_message_queue != NULL) {
        destroyMessage(g_mq_message_queue, 1);
    }
    mq_loginfo("begin deinit receiver queue");
    while (g_mq_receiver_queue != NULL) {
        destroyReceiver(g_mq_receiver_queue, 1);
    }
    mq_loginfo("begin deinit timeout");
    myTimerDeinit();
    mq_loginfo("succuss init mq");
}

void MQAddNormalMessage(TaskIDPtr id, MessageInfo description, void* data, \
        int data_length) {
    ContentPtr content = (ContentPtr)my_malloc(sizeof(Content));
    mq_debug("MQAddNormalMessage: description %s, data %s, data_length %d", \
            description, (char*)data, data_length);
    content->length = data_length;
    content->data = data;
    addMessage(MQ_NORMAL_MESSAGE, id, 0, description, content);
}

void MQAddTimeoutMessage(TaskIDPtr id, MessageInfo description, void* data, \
        int data_length, MSecond ttl)  {
    ContentPtr content = (ContentPtr)my_malloc(sizeof(Content));
    mq_debug("MQAddTimeoutMessage: ttl %d, desc %s, data %s, data_length %d", \
            ttl, description, (char*)data, data_length);
    content->length = data_length;
    content->data = data;
    addMessage(MQ_TIMEOUT_MESSAGE, id, ttl, description, content);
}

void MQAddImmediatelyReceiver(TaskIDPtr id, MessageInfo description, \
        ContentPtrPtr contentPtr) {
    mq_debug("MQAddImmediatelyReceiver: description %s, contentPtr %d", \
            description, contentPtr);
    addReceiver(id, description, 0, MQ_IMMEDIATELY_RECEIVER, NULL, NULL, \
            contentPtr);
}

void MQAddSuspendReceiver(TaskIDPtr id, MessageInfo description, MSecond ttl, \
        ContentPtrPtr contentPtr) {
    MySemaphorePtr sem = initSemaphore();
    mq_debug("MQAddSuspendReceiver: description %s, ttl %d", description, ttl);
    addReceiver(id, description, ttl, MQ_SUSPEND_RECEIVER, sem, NULL, \
            contentPtr);
    mq_debug("MQAddSuspendReceiver: before semaphore back");
    waitSemaphore(sem);
    mq_debug("MQAddSuspendReceiver: after semaphore back");
    destroySemaphore(sem);
}

void MQAddCallbackReceiver(TaskIDPtr id, MessageInfo description, MSecond ttl, \
       TaskCallback callback) {
    mq_debug("MQAddCallbackReceiver: description %s, ttl %d", description, ttl);
    addReceiver(id, description, ttl, MQ_CALLBACK_RECEIVER, NULL, callback, \
            NULL);
} 
