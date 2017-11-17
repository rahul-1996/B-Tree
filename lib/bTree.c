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


//----------------- SEARCH --------------------------------------------------------

bTreeNode *search(bTree *tree, int position, Record *record) {
    int i = 0;
    bTreeNode *r = read_array(tree,position);
    while(i < r->size && record->key > r->records[i].key) {
        i++;
    }
    if(i<r->size && record->key==r->records[i].key) {
        return read_array(tree,r->pos);
    }
    else if(r->leaf) {
        return NULL;
    }
    else {
        bTreeNode *child = read_array(tree, r->children[i]);
        return search(tree, r->children[i], record); 
    }
}


//----------------- INSERT --------------------------------------------------------

void insert(bTree **tree, Record *record) {
    // If first insert, next->pos will be zero.
    if((*tree)->next_pos == 0) {
        bTreeNode *r = node_init((*tree), true);
        r->records[0] = *record; //Check
        r->size += 1;
        (*tree)->next_pos +=1 ;
        write_array((*tree),r);
    }
    else {
        bTreeNode *r = read_array((*tree),(*tree)->root);
        if(r->size == 2*t-1) {
            bTreeNode *s = node_init((*tree), false);
            (*tree)->next_pos += 1;
            s->children[0] = (*tree)->root;
            splitChild((*tree), &s, 0, &r);  
            int c = 0;
            if(record->key > s->records[0].key) {
                c += 1;
            }
            (*tree)->root = s->pos;                
            s = read_array((*tree), s->pos);
            bTreeNode *child = read_array((*tree),s->children[c]);
            insert_nonfull((*tree), &child, record);
            write_array((*tree), s);
        }
        else {
            bTreeNode *root = read_array((*tree),(*tree)->root);     
            //printf("Next postiion to insert is: %d\n",tree->next_pos);
            //printf("Root is a %d\n", root->leaf);       
            insert_nonfull((*tree), &root, record);
        }    //printf("r->size is %d\n", r->size);
    }
    //printf("\nRoot of tree is %d\n", (*tree)->root);                    
}


void splitChild(bTree* tree, bTreeNode **x, int i, bTreeNode **y) {
    //Create an empty node z and if y is a leaf, z is also a leaf node.
    bTreeNode *z = node_init( tree, (*y)->leaf);
    z->size = t-1;
    // Copy over half of y's records to z.
    for(int j=0; j<t-1; j++) {
        z->records[j] = (*y)->records[j+t];
    }
    // If y is not a leaf, copy over the children also.
    if((*y)->leaf == false) {
        for(int j=0;j<t;j++) {
            z->children[j] = (*y)->children[j+t];
        }
    }
    // Adjust the size of y to its new size. 
    (*y)->size = t-1;
    // Move children by 1 to the right so that z can be inserted.
    for(int j=(*x)->size;j>=i+1;j--) {
        (*x)->children[j+1] = (*x)->children[j];
    }
    //Setting z as a child of i
    //printf("\nposition of child is %d\n",z->pos);
    (*x)->children[i+1] = z->pos;
    //Shift records to the right by 1 so that one record from y can be pushed up.
    for(int j=(*x)->size-1;j>=i;j--) {
        (*x)->records[j+1] = (*x)->records[j];
    }
    (*x)->records[i] = (*y)->records[t-1];
    (*x)->size += 1;
    write_array(tree, (*x));
    write_array(tree, (*y));
    write_array(tree, z);
}

void insert_nonfull(bTree *tree, bTreeNode **node, Record *record) {
    int i = (*node)->size - 1;
    if((*node)->leaf) {
        while(i>=0 && record->key < (*node)->records[i].key) {
            (*node)->records[i+1] = (*node)->records[i];
            i = i-1;
        }
        (*node)->records[i+1] = *record ;
        (*node)->size += 1; 
        write_array(tree,(*node));
        return;
    }
    else {
        while(i>=0 && (*node)->records[i].key > record->key ) {
            i = i-1;
        }
        bTreeNode *child = read_array(tree, (*node)->children[i+1]);
        if(child->size == (2*t-1)) {
            tree->next_pos+=1;
            child = read_array(tree, (*node)->children[i+1]);
            splitChild(tree, &(*node), i+1, &child);
            (*node)->leaf = false;
            if(record->key > (*node)->records[i+1].key) {
                i+=1 ;
            }
        }
        child = read_array(tree, (*node)->children[i+1]);
        insert_nonfull(tree, &child, record);
    }
}





// ***************************** DELETE ***************************************** //

/*
Citation : The following geeksforgeeks link was used as a reference 
           to implement delete due to lack of pseudo code for delete in CLRS.
           http://www.geeksforgeeks.org/b-tree-set-3delete/
*/

int findKey(bTreeNode* node, int k) {
    int idx=0;
    while (idx < node->size && node->records[idx].key < k) {
        ++idx;
    }
    return idx;
} 

void deleteNode(bTree* tree, bTreeNode* node, Record *k) {
    int idx = findKey(node, k->key);
    // The key to be removed is present in this node
    if (idx < node->size && node->records[idx].key == k->key) {
        // If the node is a leaf node - removeFromLeaf is called
        // Otherwise, removeFromNonLeaf function is called
        if (node->leaf) {
            removeFromLeaf(tree, node, idx);
        }
        else {
            removeFromNonLeaf(tree, node, idx);
        }        
        write_array(tree, node);
    }
    else {
        // If this node is a leaf node, then the key is not present in tree
        if (node->leaf) {
            printf("The record does not exist in the tree\n");
        }
        // The key to be removed is present in the sub-tree rooted with this node
        // The flag indicates whether the key is present in the sub-tree rooted
        // with the last child of this node
        bool flag = ( (idx==node->size)? true : false );
        // If the child where the key is supposed to exist has less that t keys,
        // we fill that child
        bTreeNode *child = read_array(tree, node->children[idx]) ;
        if (child->size < t) {
                fill(tree, node, idx);
        }
        // If the last child has been merged, it must have merged with the previous
        // child and so we recurse on the (idx-1)th child. Else, we recurse on the
        // (idx)th child which now has atleast t keys
        if (flag && idx > node->size) {
            //-----------------------------------------------------
            bTreeNode *sibling = read_array(tree, node->children[idx-1]);
            read_array(tree, node->children[idx-1]);
            deleteNode(tree, sibling, k);
            write_array(tree, sibling) ;
        }
        else {
            deleteNode(tree, child, k);
        }
        write_array(tree, child);
    }
}
 
// A function to remove the idx-th key from this node - which is a leaf node
void removeFromLeaf (bTree* tree, bTreeNode *node, int idx) {
    // Move all the keys after the idx-th pos one place backward
    for (int i=idx+1; i<node->size; i++)
        node->records[i-1] = node->records[i];
    // Reduce the count of keys
    node->size--;
    return;
}
 
// A function to remove the idx-th key from this node - which is a non-leaf node
void removeFromNonLeaf(bTree* tree, bTreeNode *node, int idx) {
    Record *k = &(node->records[idx]);
    bTreeNode *child = read_array(tree, node->children[idx]);
    bTreeNode *sibling = read_array(tree, node->children[idx+1]);
    // If the child(sibling) that precedes k (child idx) has atleast t keys,
    // find the predecessor 'pred' of k in the subtree rooted at
    // child idx. Replace k by pred. Recursively delete pred
    // in child idx
    if (child->size >= t) {
        Record *pred = getPred(tree, node, idx);
        node->records[idx] = *pred;
        deleteNode(tree, child, pred);
    }
    // If the child child idx has less that t keys, examine sibling.
    // If sibling has atleast t keys, find the successor 'succ' of k in
    // the subtree rooted at sibling
    // Replace k by succ
    // Recursively delete succ in sibling
    else if(sibling->size >= t)
    {
        Record *succ = getSucc(tree, node, idx);
	    //printf("%d ", succ->key);
		//printf("%s ",succ->country);
        node->records[idx] = *succ;
        deleteNode(tree, sibling, succ);
    }
 
    // If both child idx and sibling has less that t keys,merge k and all of sibling
    // into child idx
    // Now child idx contains 2t-1 keys
    // Free sibling and recursively delete k from child idx
    else {
        merge(tree, node, idx);
        deleteNode(tree, child, k);
    }
    write_array(tree, node);
    write_array(tree, child);
    write_array(tree, sibling);
    return;
}
 
// A function to get predecessor of keys[idx]
Record *getPred(bTree* tree, bTreeNode *node, int idx) {
    // Keep moving to the right most node until we reach a leaf
    bTreeNode *curr = read_array(tree, node->children[idx]);
    while (curr->leaf == false) {
        curr = read_array(tree, curr->children[curr->size]);
    }
    // Return the last key of the leaf
    return &(curr->records[curr->size-1]);
}
 
Record *getSucc(bTree* tree, bTreeNode *node, int idx) {
    // Keep moving the left most node starting from sibling until we reach a leaf
    bTreeNode *curr = read_array(tree, node->children[idx+1]);
    while (!curr->leaf) {
        read_array(tree, curr->children[0]);
    }
    // Return the first key of the leaf
    return &(curr->records[0]);
}
 
// A function to fill child child idx which has less than t-1 keys
void fill(bTree* tree, bTreeNode *node, int idx) {
    bTreeNode *prevChild = read_array(tree, node->children[idx-1]); 
    bTreeNode *succChild = read_array(tree, node->children[idx+1]);
    // If the previous child(C[idx-1]) has more than t-1 keys, borrow a key
    // from that child
    if (idx!=0 && prevChild->size >= t)
        borrowFromPrev(tree, node, idx);
    // If the next child(sibling) has more than t-1 keys, borrow a key
    // from that child
    else if (idx!=node->size && succChild->size >= t)
        borrowFromNext(tree, node, idx);
    // Merge child idx with its sibling
    // If child idx is the last child, merge it with with its previous sibling
    // Otherwise merge it with its next sibling
    else {
        if (idx != node->size)
            merge(tree, node, idx);
        else
            merge(tree, node, idx-1);
    }
    return;
}
 
// A function to borrow a key from C[idx-1] and insert it
// into child idx

void borrowFromPrev(bTree* tree, bTreeNode *node, int idx) {
    bTreeNode *child = read_array(tree, node->children[idx]);
    bTreeNode *sibling = read_array(tree, node->children[idx-1]);
    // The last key from C[idx-1] goes up to the parent and key[idx-1]
    // from parent is inserted as the first key in child idx. Thus, 
    // sibling loses one key and child gains one key
    // Moving all key in child idx one step ahead
    for (int i=child->size-1; i>=0; i--)
        child->records[i+1] = child->records[i];
 
    // If child idx is not a leaf, move all its child pointers one step ahead
    if (!child->leaf) {
        for(int i=child->size; i>=0; --i)
            child->children[i+1] = child->children[i];
    }
 
    // Setting child's first key equal to keys[idx-1] from the current node
    child->records[0] = node->records[idx-1];
 
    // Moving sibling's last child as child idx's first child
    if (!node->leaf)
        child->children[0] = sibling->children[sibling->size];
 
    // Moving the key from the sibling to the parent
    // This reduces the number of keys in the sibling
    node->records[idx-1] = sibling->records[sibling->size-1];
    child->size += 1;
    sibling->size -= 1;
    write_array(tree, node);
    write_array(tree, child);
    write_array(tree, sibling);
    return;
}
 
// A function to borrow a key from the sibling and place
// it in child idx
void borrowFromNext(bTree* tree, bTreeNode *node, int idx) {
 
    bTreeNode *child = read_array(tree, node->children[idx]);
    bTreeNode *sibling = read_array(tree, node->children[idx+1]);
    // keys[idx] is inserted as the last key in child idx
    child->records[(child->size)] = node->records[idx];

    // Sibling's first child is inserted as the last child
    // into child idx
    if (!(child->leaf))
        child->children[(child->size)+1] = sibling->children[0];
 
    //The first key from sibling is inserted into keys[idx]
    node->records[idx] = sibling->records[0];
 
    // Moving all keys in sibling one step behind
    for (int i=1; i<sibling->size; ++i)
        sibling->records[i-1] = sibling->records[i];
 
    // Moving the child pointers one step behind
    if (!sibling->leaf) {
        for(int i=1; i<=sibling->size; ++i)
            sibling->children[i-1] = sibling->children[i];
    }
    // Increasing and decreasing the key count of child idx and sibling
    // respectively
    child->size += 1;
    sibling->size -= 1;
    write_array(tree, node);
    write_array(tree, child);
    write_array(tree, sibling);   
    return;
}
 
// A function to merge child idx with sibling
// sibling is freed after merging
void merge(bTree* tree, bTreeNode *node, int idx) {
    
    bTreeNode *child = read_array(tree, node->children[idx]);
    bTreeNode *sibling = read_array(tree, node->children[idx+1]);
    // Pulling a key from the current node and inserting it into (t-1)th
    // position of child idx
    child->records[t-1] = node->records[idx];
    // Copying the keys from sibling to child idx at the end
    for (int i=0; i<sibling->size; ++i)
        child->records[i+t] = sibling->records[i];
    // Copying the child pointers from sibling to child idx
    if (!child->leaf) {
        for(int i=0; i<=sibling->size; ++i)
            child->children[i+t] = sibling->children[i];
    }
    // Moving all keys after idx in the current node one step before -
    // to fill the gap created by moving keys[idx] to child idx
    for (int i=idx+1; i<node->size; ++i)
        node->records[i-1] = node->records[i];
 
    // Moving the child pointers after (idx+1) in the current node one
    // step before
    for (int i=idx+2; i<=node->size; ++i)
        node->children[i-1] = node->children[i];
 
    // Updating the key count of child and the current node
    child->size += sibling->size+1;
    node->size = node->size-1;
    write_array(tree, node);
    write_array(tree, child);
    write_array(tree, sibling);
    //free(sibling);
    //free_array(tree, sibling); 
    return;
}

