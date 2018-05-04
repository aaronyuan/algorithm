.PHONY: clean

avl_tree_test: avl_tree.o avl_tree_test.o

all: avl_tree_test

debug: avl_tree.c avl_tree.h avl_tree_test.c
	gcc -g avl_tree.c avl_tree.h avl_tree_test.c -o avl_tree_test

clean:
	-rm -rf *.o avl_tree_test

