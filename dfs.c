#include "dfs.h"
#include <stdlib.h>
#include <stdio.h>

btree_node* make_btree_node(int data, btree_node *lchild, btree_node *rchild) {
    btree_node *n = (btree_node*) malloc(sizeof(btree_node));
    if (n == NULL) {
        fprintf(stderr, "malloc failed to create btree_node\n");
        exit(EXIT_FAILURE);
    }
    n->data = data;
    n->lchild = lchild;
    n->rchild = rchild;
    return n;
}

void stack_push(stack* s , btree_node* n) {

}
 
bool stack_empty(const stack* s) { 
    return false;
}

btree_node* stack_pop(stack* s) {
    return NULL;
}

node* dfs(btree_node *root) {
    return NULL;
}
