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
	if (root == nil_p) {
		return;
	}


	printf("%d(%s) ", root->key, root->c == black ? "b" : "r");
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

void rb_insert(node_t **root, node_t *z)
{
	node_t *x, *y;

	y = nil_p;
	x = *root;

	while (x != nil_p) {
		y = x;

		if (z->key < x->key) {
			x = y->left;
		} else {
			x = y->right;
		}
	}

	z->parent = y;

	if (y == nil_p) {
		*root = z;
	} else if (z->key < y->key) {
		y->left = z;
	} else {
		y->right = z;
	}

	z->c = red;
	z->left = nil_p;
	z->right = nil_p;

	rb_insert_fixup(root, z);
}

void rb_insert_fixup(node_t **root, node_t *z)
{
	node_t *y;

	while (z->parent->c != black) {
		if (z->parent->parent->left == z->parent) {
			/* y is z's uncle */
			y = z->parent->parent->right;

			if (y->c == red) {
				/* case 1: uncle is a red node */
				z->parent->c = black;
				z->parent->parent->c = red;
				y->c = black;
				z = z->parent->parent;
			} else {
				/* uncle is a black one */
				if (z == z->parent->right) {
					/* case 2: z is right child */
					z = z->parent;
					left_rotate(root, z);
				}
				/* case 3: z is left child */
				z->parent->c = black;
				z->parent->parent->c = red;
				right_rotate(root, z->parent->parent);
			}
		} else {
			y = z->parent->parent->left;

			if (y->c == red) {
				z->parent->c = black;
				z->parent->parent->c = red;
				y->c = black;
				z = z->parent->parent;
			} else {
				if (z == z->parent->left) {
					z = z->parent;
					right_rotate(root, z);
				}
				z->parent->c = black;
				z->parent->parent->c = red;
				left_rotate(root, z->parent->parent);
			}
		}
	}

	(*root)->c = black;
}
