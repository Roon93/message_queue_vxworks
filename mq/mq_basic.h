#ifndef MQ_BASIC
#define MQ_BASIC

#include "../memory/memory_manage.h"
#include "../timer/timer.h"
#include "../common/common.h"
#include "mq_log.h"
#include "mq_log.h"

typedef enum {
    /* message will be kept in the queue if there is no receiver which match it*/
    MQ_NORMAL_MESSAGE,
    /* message will timeout and removed if there is no receiver which match it*/
    /* in the given time*/
    MQ_TIMEOUT_MESSAGE
} MessageType;
typedef enum {
    /* receiver scan the message queue at first, either matched a message or */
    /* matched nothing, it will return immediately*/
    MQ_IMMEDIATELY_RECEIVER,
    /* receiver will be kept in the queue with limit time if there is not */
    /* message matchs it*/
    MQ_SUSPEND_RECEIVER, 
    /* receiver's callback function will be called if there is a message matchs*/
    /* it in the limit time*/
    MQ_CALLBACK_RECEIVER
} ReceiverType;

typedef char* MessageInfo; /* the message description*/

/* the content of the message loaded*/
typedef struct Content {
    int length;
    void* data;
} Content, *ContentPtr, **ContentPtrPtr;

typedef struct Message {
    MessageType type;   /* the type of the message*/
    TaskIDPtr sender;   /* the sender's taskid */
    MSecond ttl;        /* the time to live, valid if it is a timeout message*/
    MessageInfo desc;   /* the description of the message*/
    TimerID tid;        /* the timer id, valid if it is a timeout message*/
    ContentPtr content; /* the content of the message loaded*/
    struct Message* next;
    struct Message* pre;
} Message, *MessagePtr;

typedef struct Receiver {
    TaskIDPtr id;             /* the receiver's taskid*/
    MessageInfo desc;         /* the desired message description*/
    MSecond ttl;              /* the time to live, valid if it isn't immediately*/
    ReceiverType type;        /* the type of the receiver*/
    TaskCallback callback;    /* the callback function*/
    MySemaphorePtr sem;       /* the sem, valid fi it is a suspend receiver*/
    TimerID tid;              /* the tid, valid if it isn't immediately*/
    ContentPtrPtr contentPtr; /* the content pointer*/
    struct Receiver* next;
    struct Receiver* pre;
} Receiver, *ReceiverPtr;

extern MessagePtr g_mq_message_queue;   /* the global message queue*/
extern ReceiverPtr g_mq_receiver_queue; /* the global receiver queue*/

extern MySemaphorePtr g_mq_global_info_sem; /* the semaphore for mq global*/
#endif
