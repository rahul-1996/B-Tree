#include <stdbool.h>
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

typedef struct bTree{
    //char fname[20];
	//FILE *fp;
	int root;
	int next_pos;
}bTree;

bTreeNode *node_init(bool leaf, int pos);


