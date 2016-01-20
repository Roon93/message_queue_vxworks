#include "memory_manage.h"

memory_info_ptr g_memory_info = NULL;

int init_memory_manage(int log_level) {
    int i = 0;
    set_memory_log_level(log_level);
    initMemoryGlobalInfoLock();
    memory_loginfo("Begin initialization.");
    g_memory_info = (memory_info_ptr)malloc(sizeof(memory_info));
    /* initialize related info*/
    if (g_memory_info != NULL) {
        g_memory_info->chunk_list = NULL;
        g_memory_info->chunk_total = 0;
        g_memory_info->free_block_total = 0;
        g_memory_info->category_map_BST = NULL;
        g_memory_info->total_blocks = 0;
        for (i = 0; i < CATEGORY_NUM; i ++) {
            g_memory_info->chunk_category[i] = 0;
            g_memory_info->free_block_chains[i] = NULL;
            g_memory_info->free_block_num[i] = 0;
            g_memory_info->total_category_blocks[i] = 0;
        }
        memory_loginfo("Initialize successed.");
        return 0;
    } else {
        return 1;
    }
}

void deinit_memory_manage() {
    chunk_ptr tmp_chunk;
    block_ptr tmp_block;
    int i;
    /* free chunks*/
    memory_loginfo("free chunks");
    lockMemoryGlobalInfo();
    while (g_memory_info->chunk_list) {
        tmp_chunk = g_memory_info->chunk_list;
        g_memory_info->chunk_list = tmp_chunk->next;
        free(tmp_chunk->addr);
        free(tmp_chunk);
    }
    /* free bst*/
    memory_loginfo("free bst");
    destroyBST(g_memory_info->category_map_BST);
    /* free free block chain*/
    memory_loginfo("free free block chain");
    for (i = 0; i < CATEGORY_NUM; i ++) {
        memory_debug("free category %d free block chain", i);
        while (g_memory_info->free_block_chains[i]) {
            tmp_block = g_memory_info->free_block_chains[i];
            g_memory_info->free_block_chains[i] = tmp_block->next;
            free(tmp_block);
        }
    }
    free(g_memory_info);
    g_memory_info = NULL;
    memory_loginfo("deinit successed");
    unlockMemoryGlobalInfo();
    destroyMemoryGlobalInfoLock();
}

void* my_malloc(int size) {
    memory_loginfo("alloc memory %d", size);
    return getMemory(g_memory_info, size);
}

int my_free(void* ptr) {
    if (ptr == NULL) {
        return 0;
    }
    memory_loginfo("free memory.");
    /* if free successed, set ptr NULL*/
    return freeMemory(g_memory_info, ptr);
}

void showStatus() {
    int i = 0;
    lockMemoryGlobalInfo();
    printf("<------------------------------------------------------------>\n");
    printf("Total chunks: %d\n", g_memory_info->chunk_total);
    printf("Total blocks: %d\n", g_memory_info->total_blocks);
    printf("Total free blocks: %d\n\n", g_memory_info->free_block_total);

    for (i = 0; i < CATEGORY_NUM; i ++) {
        printf("Type: %s\n", memo_category_str[i]);
        printf("chunk num: %d\n", g_memory_info->chunk_category[i]);
        printf("free blocks num: %d\n", g_memory_info->free_block_num[i]);
        printf("total blocks num: %d\n", g_memory_info->total_category_blocks[i]);
    }
    printf("^____________________________________________________________>\n\n");
    unlockMemoryGlobalInfo();
}
