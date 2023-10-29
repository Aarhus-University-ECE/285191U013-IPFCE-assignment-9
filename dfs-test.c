#include <stdlib.h>

#include "dfs.h"

// These functions are used to make creating btree_node easier
btree_node *leaf(const int val) { return make_btree_node(val, NULL, NULL); }
btree_node *left(const int val, btree_node *l) {
  return make_btree_node(val, l, NULL);
}
btree_node *right(const int val, btree_node *r) {
  return make_btree_node(val, NULL, r);
}

int main() {

  btree_node *tree = make_btree_node(4,
                        make_btree_node(7,
                            make_btree_node(28,
                                leaf(77),
                                leaf(23)
                            ),
                            make_btree_node(86,
                                leaf(3),
                                leaf(9))
                            ),
                        leaf(98));


    // You can experiment with your dfs() function here :)

    return 0;
}
