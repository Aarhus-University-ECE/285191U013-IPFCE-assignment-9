#pragma once
#include <stdbool.h>

typedef struct btree {
  int data;
  struct btree *lchild;
  struct btree *rchild;
} btree;

typedef struct node {
  int data;
  struct node *next;
} node;

btree *make_node(int data, btree *lchild, btree *rchild);

node* dfs(btree *root);
