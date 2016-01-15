#include "timer_core.h"

/* Timer switcher*/
static unsigned char g_timer_switcher = 1;
static TaskID g_engine_task_id;

void lockGlobalInfo() {
    waitSemaphore(g_timer_chain_sem);
    waitSemaphore(g_timer_callback_info_sem);
}

void unlockGlobalInfo() {
    postSemaphore(g_timer_chain_sem);
    postSemaphore(g_timer_callback_info_sem);
}

void* startTimer(void* args) {
    int count = 0;
    timer_debug("startTimer: start to forwarding the timer");
    while (g_timer_switcher) {
        usleep(1 * 1000);
        count ++;
        if (count == TICK) {
            decreaseTimerNode();
            count = 0;
        }
    }
    return NULL;
}

void initTimer() {
    /* @TODO start the timer task and forward timer*/
    initCallbackInfo();
    g_timer_switcher = 1;
    createTask(&g_engine_task_id, &startTimer, NULL);
}

void deinitTimer() {
    TimerNodePtr tmp_node;
    TimerItemPtr tmp_item;
    timer_debug("deinitTimer: ");
    g_timer_switcher = 0;
    while (g_timer_chain != NULL) {
        tmp_node = g_timer_chain;
        g_timer_chain = tmp_node->next;
        removeTimerNode(tmp_node);
    }
    deinitCallbackInfo();
    timer_loginfo("deinit g_timer_chain success");
}

TimerID insertTimerItem(int tick_num, TimerItemType type, MySemaphorePtr sem, \
        TaskCallback callback, void* args, TimerID tid) {
    TimerNodePtr timer_node = findTimerNode(tick_num);
    TimerItemPtr new_timer_item;

    timer_debug("insertTimerItem: tick_num %d, type %d, sem %d, tid %d", \
            tick_num, type, sem, tid);

    new_timer_item = (TimerItemPtr)my_malloc(sizeof(TimerItem));
    timer_debug("insertTimerNode: after alloc memory");
    new_timer_item->type = type;
    new_timer_item->sem = sem;
    new_timer_item->interval = tick_num;
    new_timer_item->callback = callback;
    new_timer_item->args = args;
    new_timer_item->pre = timer_node->item_head;
    new_timer_item->next = timer_node->item_head->next;
    timer_debug("insertTimerNode: after asign");
    if (timer_node->item_head->next != NULL) {
        timer_node->item_head->next->pre = new_timer_item;
    }
    timer_node->item_head->next = new_timer_item;
    timer_debug("insertTimerNode: after asign item_head");
    if (type != TIMER_SEM) { 
        timer_debug("insertTimerNode: not sem");
        tid = addCallbackItem(new_timer_item, tid);
    }
    timer_debug("insertTimerItem: end of the function, tid %d", tid);
    new_timer_item->tid = tid;
    return tid;
}

void removeTimerItem(TimerItemPtr ptr) {
    timer_debug("removeTimerItem: ptr %d", ptr);
    if (ptr != NULL) {
        ptr->pre->next = ptr->next;
        if (ptr->next != NULL) {
            ptr->next->pre = ptr->pre;
        }
        my_free(ptr);
    }
    timer_debug("removeTimerItem: success remove");
}

void activateTimerItem(TimerItemPtr ptr) {
    TaskID task_id;
    timer_debug("activateTimerItem: ptr %d, tid %d", ptr, ptr->tid);

    if (ptr->type == TIMER_SEM) {
        /* @TODO sem*/
        postSemaphore(ptr->sem);
    } else if (ptr->type != TIMER_NONE) {
        timer_debug("activateTimerItem: callback %d, args %d", ptr->callback, \
                ptr->args);
        /* @TODO call the function */
        int abc = createTask(&task_id, ptr->callback, ptr->args);
        timer_debug("activateTimerItem: abc %d", abc);
        if (ptr->type == TIMER_INTERVAL) {
            timer_debug("activateTimerItem: the TIMER_INTERVAL");
            insertTimerItem(ptr->interval, ptr->type, NULL, ptr->callback, \
                    ptr->args, ptr->tid);
            timer_debug("activateTimerItem: after insert");
        } else {
            removeCallbackItem(ptr->tid);
        }
    }
}

/* find the correspond timer node, if not find insert one*/
TimerNodePtr findTimerNode(int tick_num) {
    int sum = 0;
    int num = tick_num;
    TimerNodePtr cur = g_timer_chain;
    TimerNodePtr pre = g_timer_chain;

    timer_debug("findTimerNode: tick_num %d", tick_num);

    while (sum < num && cur != NULL) {
        sum += cur->tick_number;
        if (sum == num) {
            return cur;
        }
        pre = cur;
        cur = cur->next;
    }
    timer_debug("findTimerNode: sum %d, num %d", sum, num);
    if (cur == NULL && sum < num) {
        timer_debug("findTimerNode: insert node");
        return insertTimerNode(pre, num - sum);
    } else {
        timer_debug("findTimerNode: splitTimerNode");
        return splitTimerNode(pre, sum - num);
    }
} 

TimerNodePtr insertTimerNode(TimerNodePtr end, int tick_num) {
    TimerNodePtr new_timer_node = (TimerNodePtr)my_malloc(sizeof(TimerNode));
    new_timer_node->item_head = (TimerItemPtr)my_malloc(sizeof(TimerItem));
    new_timer_node->item_head->next = NULL;
    new_timer_node->item_head->pre = NULL;
    new_timer_node->item_head->type = TIMER_NONE;
    new_timer_node->next = NULL;
    new_timer_node->tick_number = tick_num;
    if (end == NULL) {
        /* the time node chain is empty*/
        g_timer_chain = new_timer_node;
        timer_debug("insertTimerNode: empty chain");
    } else {
        end->next = new_timer_node;
    }
    timer_debug("insertTimerNode: end %d, tick_num %d", end, tick_num);
    return new_timer_node;
}

TimerNodePtr splitTimerNode(TimerNodePtr cur, int tick_num) {
    TimerNodePtr new_timer_node = (TimerNodePtr)my_malloc(sizeof(TimerNode));
    timer_debug("splitTimerNode: tick_num %d, before %d", tick_num, cur->tick_number);
    new_timer_node->tick_number = tick_num;
    new_timer_node->item_head = cur->item_head;
    new_timer_node->next = cur->next;
    cur->tick_number -= tick_num;
    cur->item_head = (TimerItemPtr)my_malloc(sizeof(TimerItem));
    cur->item_head->next = NULL;
    cur->item_head->pre = NULL;
    cur->item_head->type = TIMER_NONE;
    cur->next = new_timer_node;
    timer_debug("splitTimerNode: first_part %d, second_part %d", cur->tick_number, \
            new_timer_node->tick_number);
    return cur;
}

void removeTimerNode(TimerNodePtr ptr) {
    TimerItemPtr tmp_item = ptr->item_head;
    while (ptr->item_head != NULL) {
        tmp_item = ptr->item_head;
        ptr->item_head = tmp_item->next;
        my_free(tmp_item);
    }
    timer_debug("removeTimerNode: ptr %d", ptr);
    my_free(ptr);
}

void decreaseTimerNode() {
    TimerNodePtr tmp_node = g_timer_chain;
    TimerItemPtr tmp_item;
    if (g_timer_chain == NULL) {
        timer_debug("decreaseTimerNode: g_timer_chain is empty");
        return;
    }
    timer_debug("decreaseTimerNode: before tick_num %d", tmp_node->tick_number);
    tmp_node->tick_number --;
    if (tmp_node->tick_number == 0) {
        timer_debug("decreaseTimerNode: activate timers");
        while (tmp_node->item_head != NULL) {
            tmp_item = tmp_node->item_head;
            tmp_node->item_head = tmp_item->next;
            activateTimerItem(tmp_item);
            my_free(tmp_item);
        }
        timer_debug("decreaseTimerNode: after activate");
        g_timer_chain = tmp_node->next;
        my_free(tmp_node);
    }
    timer_debug("decreaseTimerNode: end of");
}
