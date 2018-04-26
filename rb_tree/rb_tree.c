#include "rb_tree.h"

void left_rotate(node_t *z)
{
	node_t *y;

	y = z->right;
	if (y == nil) {
		printf("%s: node's right child is nil\n");
        assert(1);
	}

	if (z->parent == nil) {
		root = y;
	} else if (z->parent->left == z) {
		z->parent->left = y;
	} else {
		z->parent->right = y;
	}

}
