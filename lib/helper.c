#include "../include/bTree.h"

void print_tree(bTree *tree, int pos) {
	bTreeNode *node = read_array(tree,pos);
	disp_node(node);
	for(int i=0;i<2*t;i++) {
		if(node->children[i]!=-1) 
			print_tree(tree, node->children[i]);
	}
}


void write_array(bTree *tree, bTreeNode *node) {
    tree->nodes[node->pos] = node;
}

bTreeNode *read_array(bTree *tree, int position) {
    return (tree->nodes[position]);
}

/*
void free_array(bTree *tree, bTreeNode *node) {
    free(tree->nodes[node->pos]);
}
*/