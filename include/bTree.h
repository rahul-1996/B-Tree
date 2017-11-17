#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __BTREE_H__
#define __BTREE_H__

typedef struct {
    int key;
    char country[3];
    char grate[4];
    int score;
    int rate;
}Record;

typedef struct {
    int size;
    int pos;
    bool leaf;    
    Record records[2*t-1];
    int children[2*t];
}bTreeNode;

typedef struct {
    //char fname[20];
    FILE *fp;
    int root;
    int next_pos;
    bTreeNode *nodes[100000];
}bTree;


bTreeNode *node_init(bTree *tree, bool leaf);
bTree *bTree_init();
void write_array(bTree *tree, bTreeNode *node);
bTreeNode *read_array(bTree *tree, int position);
void splitChild(bTree* tree, bTreeNode **x, int i, bTreeNode **y);
void insert_nonfull(bTree *tree, bTreeNode **node, Record *record);
void insert(bTree **tree, Record *record);
void disp_node(bTreeNode* p);
void print_tree(bTree *tree, int pos);
bTreeNode *search(bTree *tree, int position, Record *record);
void deleteNode(bTree* tree, bTreeNode* node, Record* k);
void removeFromLeaf(bTree *tree, bTreeNode *node, int idx);
void removeFromNonLeaf(bTree *tree, bTreeNode *node, int idx);
Record *getPred(bTree* tree, bTreeNode *node, int idx);
Record *getSucc(bTree* tree, bTreeNode *node, int idx);
void fill(bTree *tree, bTreeNode *node, int idx);
void borrowFromPrev(bTree* tree, bTreeNode *node, int idx);
void borrowFromNext(bTree* tree, bTreeNode *node, int idx);
void merge(bTree* tree, bTreeNode *node, int idx);
void free_array(bTree *tree, bTreeNode *node);

#endif
