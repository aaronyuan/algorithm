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

void rb_transplant(node_t **root, node_t *u, node_t *v)
{
	if (u->parent == nil_p) {
		*root = v;
	} else if (u->parent->left == u) {
		u->parent->left = v;
	} else {
		u->parent->right = v;
	}

	v->parent = u->parent;
}

node_t *rb_minimum(node_t *y)
{
	node_t *x = y;

	while (y->left != nil_p) {
		x = y;
		y = y->left;
	}

	return x;
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

void rb_delete(node_t **root, node_t *z)
{
	node_t *y = z;
	node_t *x = NULL;
	enum color y_orig_c;

	y_orig_c = z->c;

	if (z->left == nil_p) {
		x = z->right;
		rb_transplant(root, z, z->right);
	} else if (z->right == nil_p) {
		x = z->left;
		rb_transplant(root, z, z->left);
	} else {
		y = rb_minimum(z->right);
		y_orig_c = y->c;
		x = y->right;

		if (y->parent == z) {
			x->parent = y;
		} else {
			rb_transplant(root, y, y->right);
			y->parent->left = x;
			y->right = z->right;
		}

		rb_transplant(root, z, y);
		y->left = z->left;
		y->c = z->c;
	}

	if (y_orig_c == black) {
		rb_delete_fixup(root, x);
	}
}

void rb_delete_fixup(node_t **root, node_t *x)
{
	node_t *w;

	while (x != *root && x->c == black) {
		if (x == x->parent->left) {
			w = x->parent->right;

			/* case 1: x's uncle is red */
			if (w->c == red) {
				w->c = black;
				x->parent->c = red;

				left_rotate(root, x->parent);
				w = x->parent->right;
			}

			/* case 2: x's uncle is black and has 2 black children */ 
			if (w->left->c == black && w->right->c == black) {
				w->c = red;
				x = x->parent;
			} else {
				/* case 3: left child of x's uncle is red */
				if (w->right->c == black) {
					w->c = red;
					w->left->c = black;
					right_rotate(root, w);
					w = x->parent->right;
				}

				/* case 4: right child of x's uncle is red */
				w->c = x->parent->c;
				x->parent->c = black;
				w->right->c = black;
				left_rotate(root, x->parent);

				x = *root;
			}
		} else {
			w = x->parent->left;

			if (w->c == red) {
				w->c = black;
				x->parent->c = red;

				right_rotate(root, x->parent);
				w = x->parent->left;
			}

			if (w->left->c == black && w->right->c == black) {
				w->c = red;
				x = x->parent;
			} else {
				if (w->left->c == black) {
					w->c = red;
					w->right->c = black;
					left_rotate(root, w);
					w = x->parent->left;
				}

				w->c = x->parent->c;
				x->parent->c = black;
				w->left->c = black;
				right_rotate(root, x->parent);

				x = *root;
			}
		}
	}

	x->c = black;
}
