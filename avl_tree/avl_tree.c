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

void right_rotate(node_t **root, node_t *x)
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
}

void left_rotate(node_t **root, node_t *x)
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
}

void balance(node_t **root, node_t *x)
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
			left_rotate(root, y);
		}
		right_rotate(root, x);
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
			right_rotate(root, y);
		}
		left_rotate(root, x);
	}
}

void avl_insert(node_t **root, node_t *z)
{
}
