#pragma once
#include <stdbool.h>

typedef struct btree_node {
  int data;
  struct btree_node *lchild;
  struct btree_node *rchild;
} btree_node;

btree_node *make_btree_node(int data, btree_node *lchild, btree_node *rchild);

typedef struct ll_btree_node {
  btree_node* data;
  struct ll_btree_node *next;
} ll_btree_node;

typedef struct stack {
  ll_btree_node *head;
} stack;

void stack_push(stack*, btree_node*);
bool stack_empty(const stack*);
btree_node* stack_pop(stack*);

// The `node` struct is used to store the dfs result in a linked list
// e.g. if you have the tree
//      3
//    /  \
//   2    5
// Then the result will be
// 3 -> 2 -> 5 -> NULL
typedef struct node {
  int data;
  struct node *next;
} node;

node* dfs(btree_node *root);

