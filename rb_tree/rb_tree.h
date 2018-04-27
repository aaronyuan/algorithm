#ifndef _RB_TREE_H_
#define _RB_TREE_H_

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

extern node_t *nil_p;

void left_rotate(node_t **, node_t *);
void right_rotate(node_t **, node_t *);
void preorder_walk(node_t *);

void rb_insert(node_t **, node_t *);
void rb_insert_fixup(node_t **, node_t *);

#endif	/* _RB_TREE_H_ */
