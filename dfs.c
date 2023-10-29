#include "dfs.h"
#include <stdlib.h>
#include <stdio.h>

btree* make_node(int data, btree *lchild, btree *rchild) {
    btree *n = (btree*) malloc(sizeof(btree));
    if (n == NULL) {
        fprintf(stderr, "malloc failed to create btree\n");
        exit(EXIT_FAILURE);
    }
    n->data = data;
    n->lchild = lchild;
    n->rchild = rchild;
    return n;
}


node* dfs(btree *root) {
    return NULL;
}
