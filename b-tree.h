#include <stdbool.h>
#ifndef __BTREE_H__
#define __BTREE_H__

#define t 2

typedef struct {
    int key;
    char country[10];
    char description[10];
    int n1;
    int n2;
}Document;

typedef struct {
    int size;
    Document *document;
    bool leaf;
    struct bTreeNode *children;
}bTreeNode;

typedef struct bTree{
    bTreeNode *root;
}bTree;

btreeNode* node_init();

