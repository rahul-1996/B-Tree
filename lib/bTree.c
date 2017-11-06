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
    tree->next_pos = 0 ;
    return tree ; 
}

void write_array(bTree *tree, bTreeNode *node) {
    tree->nodes[node->pos] = *node;
}

bTreeNode *read_array(bTree *tree, int position) {
    return &(tree->nodes[position]);
}

void splitChild(bTree* tree, bTreeNode *x, int i, bTreeNode *y) {
    //Create an empty node z and if y is a leaf, z is also a leaf node.
    bTreeNode *z = node_init(y->leaf, tree->next_pos);
    z->size = t-1;
    // Copy over half of y's records to z.
    for(int j=0; j<t-1; j++) {
        z->records[j] = y->records[j+t];
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
        x->records[j+1] = x->records[j];
    }
    x->records[i] = y->records[t-1];
    x->size += 1;

    write_array(tree, x);
    write_array(tree, y);
    write_array(tree, z);
    
}

void insert_nonfull(bTree *tree, bTreeNode *node, Record *record) {
    int i = node->size - 1;
    if(node->leaf) {
        while(i>=0 && record->key < node->records[i].key) {
            node->records[i+1] = node->records[i];
            i = i-1;
        }
        node->records[i+1] = *record ;
        node->size += 1;
        write_array(tree,node);
    }
    else {
        while(i>=0 && record->key < node->records[i].key) {
            i -= 1 ;
        }
        bTreeNode *child = read_array(tree, node->children[i]);
        if(child->size = (2*t-1)) {
            splitChild(tree, node, i+1, child);
            if(record->key > node->records[i+1].key) {
                i+=1 ;
            }
        }
        insert_nonfull(tree,child,record);
    }
}

void insert(bTree *tree, Record *record) {
    // If first insert, next->pos will be zero.
    if(tree->next_pos == 0) {
        bTreeNode *r = node_init(true, tree->next_pos);
        r->records[0] = *record; //Check
        r->size += 1;
        //tree->root = r;
        tree->next_pos +=1 ;
        write_array(tree,r);
       // printf("Succesfully inserted\n");
       // printf("Size is: %d\n",tree->nodes[0].size);
    }
    else {
        bTreeNode *r = read_array(tree,0);
        if(r->size == 2*t-1) {
            //r->leaf = false;
            bTreeNode *s = node_init(false,tree->next_pos);
            tree->next_pos += 1;
            s->children[0] = r->pos;
            splitChild(tree, s, 0, r);
            int c = 0;
            if(record->key > s->records[0].key) {
                c += 1;
            }
            bTreeNode *child = read_array(tree,s->children[c]);
            insert_nonfull(tree, s, record);
            tree->root = s->pos;
        }
        else {
            insert_nonfull(tree, r, record);
        }
    }
}