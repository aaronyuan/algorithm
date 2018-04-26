#include "rb_tree.h"

node_t nil = {
	.left = NULL,
	.right = NULL,
	.parent = NULL,
	.c = black,
};

node_t *nil_p = &nil;

void preorder_walk(node_t *root)
{
	if (root == NULL || root == nil_p) {
		return;
	}


    printf("%d ", root->key);
	preorder_walk(root->left);
	preorder_walk(root->right);
}

void left_rotate(node_t **root, node_t *z)
{
	node_t *y;

	y = z->right;
	if (y == nil_p) {
		printf("%s: node's right child is nil\n", __func__);
		assert(1);
	}

	if (z->parent == nil_p) {
		*root = y;
	} else if (z->parent->left == z) {
		z->parent->left = y;
	} else {
		z->parent->right = y;
	}

	z->right = y->left;
	if (y->left != nil_p) {
		y->left->parent = z;
	}
	y->left = z;

	y->parent = z->parent;
	z->parent = y;
}

void right_rotate(node_t **root, node_t *z)
{
	node_t *y;

	y = z->left;
	if (y == nil_p) {
		printf("%s: node's left child is nil\n", __func__);
		assert(1);
	}

	if (z->parent == nil_p) {
		*root = y;
	} else if (z->parent->left == z) {
		z->parent->left = y;
	} else {
		z->parent->right = y;
	}

	z->left = y->right;
	if (y->right != nil_p) {
		y->right->parent = z;
	}
	y->right = z;

	y->parent = z->parent;
	z->parent = y;
}
