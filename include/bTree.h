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
    //FILE *fp;
    int root;
    int next_pos;
    bTreeNode nodes[1000000] ;
}bTree;

#endif

bTreeNode *node_init(bool leaf, int pos);
bTree *bTree_init();
void write_array(bTree *tree, bTreeNode *node);
bTreeNode *read_array(bTree *tree, int position);
void splitChild(bTree* tree, bTreeNode *x, int i, bTreeNode *y);
void insert_nonfull(bTree *tree, bTreeNode *node, Record *record);
void insert(bTree *tree, Record *record);
void disp_node(bTreeNode* p);
