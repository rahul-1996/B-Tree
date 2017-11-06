#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bTree.h"

/*
Citation: 
These algorithms are an implementation of the psuedo code
present in the CLRS textbook. 
*/

bTree *bTree_init() {
    bTree *tree = malloc(sizeof(bTree));
    tree->root = 0 ; 
    return tree ; 
}

void splitChild(bTree* tree, bTreeNode *x, int i, btreeNode *y) {
    //Create an empty node z and if y is a leaf, z is also a leaf node.
    bTreeNode *z = node_init(y->leaf, tree->next_pos);
    z->size = t-1;
    // Copy over half of y's records to z.
    for(int j=0; j<t-1; j++) {
        z->record[j] = y->record[j+t];
    }
    // If y is not a leaf, copy over the children also.
    if(y->leaf != true) {
        for(int j=0;j<t;j++) {
            z->children[j] = z->children[j+t];
        }
    }
    // Adjust the size of y to its new size. 
    y->size = t-1;
    // Move children by 1 to the right so that z can be inserted.
    for(int j=x->size;j>i;j--) {
        x->children[j+1] = x->children[j];
    }
    //Setting z as a child of i
    x->children[i+1] = z->pos;
    //Shift records to the right by 1 so that one record from y can be pushed up.

    for(int j=x->size-1;j>=i;j--) {
        x->record[j+1] = x->record[j];
    }
    x->record[i] = y->record[t-1];
    x->size += 1;
}

