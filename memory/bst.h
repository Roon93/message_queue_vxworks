#ifndef BASIC_STRUCT
#define BASIC_STRUCT

#include "memory_basic.h"

#endif

#include <stdlib.h>

void addNodeToBST(bst_node_ptr* root, bst_node_ptr node);

memo_category findCategoryInBST(bst_node_ptr root, addr_type addr, \
        addr_type* base);

void destroyBST(bst_node_ptr root);
