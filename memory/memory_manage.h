#include "memory_basic.h"
#include "memory.h"
#include "bst.h"
#include "memory_log.h"

/**
 * init the memory info, include the g_memory_info global variable, and its
 * related information
 */
int init_memory_manage(int log_level);

/* deinit the memory manage*/
void deinit_memory_manage();

/**
 * malloc a memory space with the give size
 *
 * params:
 *  size: the size of the memory need to malloc
 * return:
 *  the pointer of the allocated memory
 */
void* my_malloc(int size);

/**
 * free the memory of the pointer represented
 *
 * params:
 *  ptr: the memory need to be freed
 * return:
 *  0: success, 1: failed
 */
int my_free(void* ptr);

/* show the statistics of the memory pool*/
void showStatus();
