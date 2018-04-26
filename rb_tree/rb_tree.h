#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum color {
	black,
	red
};

typedef struct node {
	struct node *left;
	struct node *right;
	struct node *parent;
	enum color c;
	int key;
} node_t;

node_t nil = {
	.left = NULL;
	.right = NULL;
	.parent = NULL;
	.c = black;
};

node_t *root;
