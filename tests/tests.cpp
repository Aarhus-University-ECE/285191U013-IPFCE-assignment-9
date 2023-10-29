#include <catch2/catch_test_macros.hpp>


extern "C" {
#include <stdbool.h>

#include "dfs.h"
#include "search.h"
#include "sum.h"
}

TEST_CASE("sum") {
  // Empty array
  const int a[] = {1, -3, 1, 1, 5};
  const int len = sizeof(a) / sizeof(a[0]);
  REQUIRE(sum(a, 0) == 0);
  // Non-empty
  REQUIRE(sum(a, 5) == 5);

  {
    const int input[] {10, 9, 2, 11, 5, 12, 8, 3, 1, 4, 6, 7};
    const int len = sizeof(input) / sizeof(input[0]);
    const int expected = 0;
    for (int i = 0; i < len; i++) {
      expected += input[i];
    }

    REQUIRE(sum(input, len) == expected);
  }
}

TEST_CASE("search") {

  const int a[] = {2, -3, 1, 1, 5};
  const int len = sizeof(a) / sizeof(a[0]);
  // True
  REQUIRE(search(a, len, 5) == true);
  REQUIRE(search(a, len, 1) == true);
  REQUIRE(search(a, len, 2) == true);

  // False
  REQUIRE(search(a, len, 0) == false);
  REQUIRE(search(a, 0, 1) == false);

  {
    const int input[] = {10, 9, 2, 11, -3, 12, -3, 3, 1, 4, 6, 7};
    const int len = sizeof(input) / sizeof(input[0]);
    REQUIRE(search(input, len, -3) == true);
  }
}

node *leaf(int val) { return make_btree_node(val, NULL, NULL); }
node *left(int val, node *l) { return make_btree_node(val, l, NULL); }
node *right(int val, node *r) { return make_btree_node(val, NULL, r); }

TEST_CASE("dfs") {

  {
    btree_node *tree = make_btree_node(4,
                           make_btree_node(7, make_btree_node(28, leaf(77), leaf(23)),
                                     make_btree_node(86, leaf(3), leaf(9))),
                           leaf(98));
    node* list = dfs(tree);
    REQUIRE(list != NULL);
    node* p = list;
    REQUIRE(p->data == 4); // first
    REQUIRE(p->next != NULL);
    p = p->next;
    REQUIRE(p->data == 7); // second
    REQUIRE(p->next != NULL);
    p = p->next;
    REQUIRE(p->data == 28); // third
    REQUIRE(p->next != NULL);
    p = p->next;
    REQUIRE(p->data == 77); // fourth
    REQUIRE(p->next != NULL);
    p = p->next;
    REQUIRE(p->data == 23); // fifth
    REQUIRE(p->next != NULL);
    p = p->next;
    REQUIRE(p->data == 86); // sixth
    REQUIRE(p->next != NULL);
    p = p->next;
    REQUIRE(p->data == 3); // seventh
    REQUIRE(p->next != NULL);
    p = p->next;
    REQUIRE(p->data == 9); // eigth
    REQUIRE(p->next != NULL);
    p = p->next;
    REQUIRE(p->data == 98); // ninth
  }

  {
    // 5
    // 3 - 16
    // 1 - 4 - 10 - 18
    // 2 - 6 - 15 - 17 -19
    // 9 - 13 - 20
    // 7 - 11 - 14
    // 8 - 12
    // #let data = \
//     (5, 16, 10, 6, 15, 13, 3, 4, 1, 9, 18, 2, 14, 19, 17, 20, 11, 7, 12,
    //     8)
    // node *tree =
    //     make_node(5,
    //       make_node(3,
    //         make_node(1,
    //           leaf(2), 
    //           NULL),
    //         leaf(4)),
                  
    //               make_node(16, make_node(10, make_node(6, make, NULL)))

    //     )
  }
}
