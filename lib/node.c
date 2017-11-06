#include "../include/bTree.h"

bTreeNode *node_init(bool leaf, int pos) {
    bTreeNode *node = (bTreeNode *)malloc(sizeof(bTreeNode));
    node->size = 0;
    node->leaf = leaf;
    node->pos = pos;
    for(int i=0;i<2*t;i++) {
        node->children[i]= -1;
    }
    return node;
}

void disp_node(bTreeNode *node)
{
	printf("keys\n");
	for(int i = 0; i < node->size; i++)
	{
		printf("%d ", node->records[i].key);
		printf("%s ",node->records[i].country);
	}
	printf("\n");
	printf("links\n");
	for(int i = 0; i < node->size; i++)
	{
		printf("%d ", node->children[i]);
	}
	printf("\n");
}