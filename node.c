#include "b-tree.h"

bTreeNode *node_init(bool leaf) {
    bTreeNode *node = (bTreeNode *)malloc(sizeof(bTreeNode));
    node->size = 0;
    node->leaf = leaf;
    node->documents = malloc(sizeof(Document)*(2*t-1));
    node->children = malloc(sizeof(bTreeNode *)*(2*t));
    return node;
}

