#ifndef BASIC_STRUCT
#define BASIC_STRUCT

#include "memory_basic.h"

#endif

#include <stdlib.h>

/**
 * add node to the binary search tree.
 *
 * params:
 *  root: the root of the binary search tree
 *  node: the node need to add into the binary search tree
 * return:
 *  none
 */
void addNodeToBST(bst_node_ptr* root, bst_node_ptr node);

/**
 * find the given address category by search the bst
 *
 * params:
 *  root: the root of the binary search tree
 *  addr: the given address
 *  base: use this parameter get the base address of the chuck which the given
 *        address belongs to.
 * return:
 *  the categroy of the address belongs to.
 */
memo_category findCategoryInBST(bst_node_ptr root, addr_type addr, \
        addr_type* base);

/*
 * destroy the binary search tree, include release the space.
 * 
 * params:
 *  root: the root of the binary search tree
 * return:
 *  none.
 */
void destroyBST(bst_node_ptr root);
