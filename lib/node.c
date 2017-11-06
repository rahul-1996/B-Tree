#include "b-tree.h"

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

void disp_node(bTreeNode* p)
{
	printf("keys\n");
	for(int i = 0; i < p->n - 1; i++)
	{
		printf("%d ", p->record[i].key);
	}
	printf("\n");
	printf("links\n");
	for(int i = 0; i < p->n; i++)
	{
		printf("%d ", p->children[i]);
	}
	printf("\n");
}