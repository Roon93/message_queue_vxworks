#include "bst.h"

void addNodeToBST(bst_node_ptr* root, bst_node_ptr node) {
    bst_node_ptr cur;
    memory_debug("addNodeToBST: category %d", node->category);
    if (*root == NULL) {
        *root = node;
        return;
    }
    cur = *root;
    while (1) {
        if (node->start > cur->start) {
            if (cur->right != NULL) {
                cur = cur->right;
            } else {
                cur->right = node;
                break;
            }
        } else {
            if (cur->left != NULL) {
                cur = cur->left;
            } else {
                cur->left = node;
                break;
            }
        } /* end  of if*/
    } /* end of while*/

}

memo_category findCategoryInBST(bst_node_ptr root, addr_type addr, \
        addr_type* base) {
    bst_node_ptr cur = root;
    memory_debug("findCategoryInBST");
    while (cur) {
        memory_debug("findCategoryInBST: category %d", cur->category);
        if (addr >= cur->start && addr <= cur->end) {
            *base = cur->start;
            return cur->category;
        }
        if (addr < cur->start) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return NIL;
}

void destroyBST(bst_node_ptr root) {
    if (root == NULL) {
        return;
    }
    /* destroy left subtree*/
    if (root->left != NULL) {
        destroyBST(root->left);
        root->left = NULL;
    }
    /* destroy right subtree*/
    if (root->right != NULL) {
        destroyBST(root->right);
        root->right = NULL;
    }
    free(root);
}
