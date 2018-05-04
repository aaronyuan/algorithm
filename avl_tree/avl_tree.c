#include "avl_tree.h"

inline int node_height(node_t *x)
{
	return x == NULL ? 0 : x->height;
}

int max_height(node_t *x, node_t *y)
{
	int x_h, y_h;

	x_h = node_height(x);
	y_h = node_height(y);

	return x_h > y_h ? x_h : y_h;
}

void preorder_walk(node_t *root)
{
	if (root == NULL) {
		return;
	}

	printf("%d(h:%d) ", root->key, root->height);
	preorder_walk(root->left);
	preorder_walk(root->right);
}

node_t *minimum(node_t *x)
{
	while (x->left != NULL) {
		x = x->left;
	}

	return x;
}

void avl_transplant(node_t **root, node_t *u, node_t *v)
{
	if (u->parent == NULL) {
		*root = v;
	} else if (u->parent->left == u) {
		u->parent->left = v;
	} else {
		u->parent->right = v;
	}

	if (v != NULL) {
		v->parent = u->parent;
	}
}

node_t *right_rotate(node_t **root, node_t *x)
{
	node_t *y = NULL;

	y = x->left;
	assert(y != NULL);

	y->parent = x->parent;

	if (x->parent == NULL) {
		*root = y;
	} else if (x->parent->left == x) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}

	x->parent = y;
	x->left = y->right;

	if (y->right != NULL) {
		y->right->parent = x;
	}

	y->right = x;

	/* adjust the height of x, y */
	x->height = max_height(x->right, x->left) + 1;
	y->height = max_height(y->right, y->left) + 1;

	return y;
}

node_t *left_rotate(node_t **root, node_t *x)
{
	node_t *y = NULL;

	y = x->right;
	assert(y != NULL);

	y->parent = x->parent;

	if (x->parent == NULL) {
		*root = y;
	} else if (x->parent->left == x) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}

	x->parent = y;
	x->right = y->left;

	if (y->left != NULL) {
		y->left->parent = x;
	}

	y->left = x;

	/* adjust the height of x, y */
	x->height = max_height(x->right, x->left) + 1;
	y->height = max_height(y->right, y->left) + 1;

	return y;
}

node_t *balance(node_t **root, node_t *x)
{
	int left_height, right_height;
	node_t *y;

	left_height = node_height(x->left);
	right_height = node_height(x->right);
	
	if (left_height == right_height + 2) {
		y = x->left;
		assert(y != NULL);

		left_height = node_height(y->left);
		right_height = node_height(y->right);

		/*
		 * case 1: left-left
		 *      O
		 *     /
		 *    O
		 *   /
		 *  O
		 * case 2: left-right
		 *      O
		 *     /
		 *    O
		 *     \
		 *      O
		 */

		if (right_height > left_height) {
			/* case 2 */
			(void)left_rotate(root, y);
		}
		return right_rotate(root, x);
	} else if (right_height == left_height + 2) {
		y = x->right;
		assert(y != NULL);

		left_height = node_height(y->left);
		right_height = node_height(y->right);
		/*
		 * case 3: right-right
		 *    O
		 *     \
		 *      O
		 *       \
		 *        O
		 * case 4: right-left
		 *    O
		 *     \
		 *      O
		 *     / 
		 *    O
		 */
		if (left_height > right_height) {
			(void)right_rotate(root, y);
		}
		return left_rotate(root, x);
	} else {
		x->height = left_height > right_height ? left_height + 1 : right_height + 1;
		return x;
	}
}

void avl_insert(node_t **root, node_t *z)
{
	node_t *node = *root;
	node_t *p = NULL;

	while (node != NULL) {
		p = node;

		if (node->key < z->key) {
			node = node->right;
		} else {
			node = node->left;
		}
	}

	if (p == NULL) {
		*root = z;
	} else if (p->key < z->key) {
		p->right = z;
		z->parent = p;
	} else {
		p->left = z;
		z->parent = p;
	}

	z->left = NULL;
	z->right = NULL;
	z->height = 1;

	while (p != NULL) {
		p = balance(root, p);
		p = p->parent;
	}
}

void avl_delete(node_t **root, node_t *z)
{
	node_t *y, *x;

	if (z->left == NULL) {
		x = z->parent;
		avl_transplant(root, z, z->right);
	} else if (z->right == NULL) {
		x = z->parent;
		avl_transplant(root, z, z->left);
	} else {
		y = minimum(z->right);
		assert(y != NULL);

		if (y->parent == z) {
			x = y;
		} else {
			x = y->parent;
			avl_transplant(root, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		avl_transplant(root, z, y);
		y->left = z->left;
		y->left->parent = y;
	}

	while (x != NULL) {
		x = balance(root, x);
		x = x->parent;
	}
}
