#include "include/bTree.h"
#include <stdio.h>
#include <stdlib.h>

#define TOTAL 5

void insert_record(Record* record, int key, char country[], char grate[], int score, int rate) {
	record->key = key;
	strcpy(record->country, country);
	strcpy(record->grate, grate);
	record->score = score;
	record->rate = rate;
}

Record** read_file(Record **records, char *filepath) {
	records = malloc(sizeof(Record*)*TOTAL);
    FILE *fp = fopen(filepath, "r");
    int i=0;
	int key;
	char country[255];
	char grate[255];
	int score;
	int rate;
	while(i < TOTAL && fscanf(fp, "%d,%s,%s,%d,%d", &key, country, grate, &score, &rate)) {
		records[i] = malloc(sizeof(Record));
		insert_record(records[i], key, country, grate, score, rate);
		i++;
	}
	return records;
}

int main() {
    bTree *tree = bTree_init();
    Record **records = read_file(records,"./data/dataset.csv");
    for(int i=0;i<TOTAL;i++) {
        insert(tree, records[i]);
    }   
    printf("Node %d\n",0);
    disp_node(&tree->nodes[0]);
    printf("Node %d\n",1);    
    disp_node(&tree->nodes[1]);
    printf("Node %d\n",2);    
    disp_node(&tree->nodes[2]); 
    return 0;
}