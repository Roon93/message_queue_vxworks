#ifndef TIMER_BASIC
#define TIMER_BASIC

#include <unistd.h>    
#include "timer_log.h"
#include "../memory/memory_manage.h"
#include "../common/common.h"

/* @TODO */
#define TICK 1000     /* per tick interval*/
#define MAX_CALLBACK_NUM 100    /* Maximum callback timer number*/

typedef long long int MSecond;  /* type time */
typedef int TimerID;            /* the callback timer identify*/
typedef enum {TIMER_NONE, TIMER_SEM, TIMER_TIMEOUT, TIMER_INTERVAL} TimerItemType;

/* Timer item contain a sem post action or a callback action*/
/* Many timer item can occur at the same time*/
typedef struct TimerItem {
    TimerItemType type;     /* the type of the time item*/
    MySemaphorePtr sem;     /* if sem post action save the sem*/
    TimerID tid;            /* the tid for for timeout and interval timer*/
    int interval;           /* the interval for interval timer*/
    TaskCallback callback;  /* the callback info of this Timer Item*/
    void* args;             /* the arguments of the callback function*/
    struct TimerItem* next; 
    struct TimerItem* pre;
} TimerItem, *TimerItemPtr;

/* Timer node is the unit of timer count operation*/
/* A timer node can represent "tick_number" time unit*/
/* Timer items attach to a specify timer node and when turn to this node,*/
/* these timer items are activated.*/
typedef struct TimerNode {
    int tick_number;        /* the tick number of this node*/
    TimerItemPtr item_head; /* the chain for the attached timer items*/
    struct TimerNode* next;
} TimerNode, *TimerNodePtr;

typedef struct CallbackFreeNode {
    TimerID tid;            /* the tid of the freenode*/
    struct CallbackFreeNode* next;
} CallbackFreeNode, *CallbackFreeNodePtr;

typedef struct CallbackInfo {
   CallbackFreeNodePtr free_node_head;      /* the free callback item chain*/
   TimerItemPtr items[MAX_CALLBACK_NUM];    /* all callback item*/
} CallbackInfo, *CallbackInfoPtr;

/* The timer node chain for the timer sys, all timer operation occurs in*/
/* the chain*/
static TimerNodePtr g_timer_chain = NULL;

/* The fix size callback info structure, all callback and interval timer */
/* related the callback info*/
extern CallbackInfoPtr g_timer_callback_info;

extern MySemaphorePtr g_timer_chain_sem;
extern MySemaphorePtr g_timer_callback_info_sem;

#endif
