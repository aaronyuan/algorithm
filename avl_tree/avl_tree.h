#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node {
	struct node *parent;
	struct node *left;
	struct node *right;
	int height;
	int key;
} node_t;
