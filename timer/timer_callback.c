#include "timer_callback.h"


CallbackInfoPtr g_timer_callback_info = NULL;

void initCallbackInfo() {
    CallbackFreeNodePtr tmp;
    if (g_timer_callback_info == NULL) {
        timer_debug("initCallbackInfo: empty callback info");
        g_timer_callback_info = (CallbackInfoPtr)my_malloc(sizeof(CallbackInfo));
        g_timer_callback_info->free_node_head = NULL;
        for (int i = 0; i < MAX_CALLBACK_NUM; i ++) {
            tmp = (CallbackFreeNodePtr)my_malloc(sizeof(CallbackFreeNode));
            tmp->tid = (TimerID)i;
            tmp->next = g_timer_callback_info->free_node_head;
            g_timer_callback_info->free_node_head = tmp;
        }
    }
    timer_debug("initCallbackInfo: g_timer_callback_info %d", g_timer_callback_info);
    timer_loginfo("init callback info successful");
}

void deinitCallbackInfo() {
    CallbackFreeNodePtr tmp = g_timer_callback_info->free_node_head;
    timer_debug("deinitCallbackInfo: nothing");
    while (g_timer_callback_info->free_node_head != NULL) {
        tmp = g_timer_callback_info->free_node_head;
        g_timer_callback_info->free_node_head = tmp->next;
        my_free(tmp);
    }
    my_free(g_timer_callback_info);
    timer_loginfo("deinit callback info successful");
}

TimerID addCallbackItem(TimerItemPtr timer_item, TimerID tid) {
    TimerID new_tid;
    CallbackFreeNodePtr free_node;
    timer_debug("addCallbackItem: timer_item %d, tid %d", timer_item, tid); 
    /* timer_debug("addCallbackItem: g_timer_callback_info %d", g_timer_callback_info);*/
    timer_debug("addCallbackItem: test");
    if (tid != -1) {
        timer_debug("addCallbackItem: tid not -1 %d", tid);
        if (g_timer_callback_info == NULL) {
            timer_debug("addCallbackItem: the g_timer_callback_info is NULL");
        }
        g_timer_callback_info->items[tid] = timer_item;
        return tid;
    } else {
        timer_debug("addCallbackItem: tid is -1 %d", tid);
        if (g_timer_callback_info->free_node_head == NULL) {
            return -1;
        }
        free_node = g_timer_callback_info->free_node_head;
        g_timer_callback_info->free_node_head = free_node->next;
        new_tid = free_node->tid;
        my_free(free_node);
        g_timer_callback_info->items[new_tid] = timer_item;
        timer_debug("addCallbackItem: new_tid %d", new_tid);
        return new_tid;
    }
}

void removeCallbackItem(TimerID tid) {
    CallbackFreeNodePtr tmp;

    timer_debug("removeCallbackItem: tid %d", tid);

    tmp = (CallbackFreeNodePtr)my_malloc(sizeof(CallbackFreeNode));
    tmp->next = g_timer_callback_info->free_node_head;
    g_timer_callback_info->free_node_head = tmp;
    g_timer_callback_info->items[tid] = NULL;
}
