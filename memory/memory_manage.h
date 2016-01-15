#ifndef BASIC_STRUCT
#define BASIC_STRUCT

#include "memory_basic.h"

#endif

#include "memory.h"
#include "bst.h"
#include "memory_log.h"

memory_info_ptr g_memory_info;


int init_memory_manage();

void deinit_memory_manage();

void* my_malloc(int size);

/* 0: success, 1: failed*/
int my_free(void* ptr);

void showStatus();
