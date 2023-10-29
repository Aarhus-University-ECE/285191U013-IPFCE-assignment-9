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
  REQUIRE(sum(a, len) == 5);

  {
    const int input[] {10, 9, 2, 11, 5, 12, 8, 3, 1, 4, 6, 7};
    const int len = sizeof(input) / sizeof(input[0]);
    int expected = 0;
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

btree_node *leaf(int val) { return make_btree_node(val, NULL, NULL); }
btree_node *left(int val, btree_node *l) { return make_btree_node(val, l, NULL); }
btree_node *right(int val, btree_node *r) { return make_btree_node(val, NULL, r); }

TEST_CASE("dfs", "[dfs]") {

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

}


TEST_CASE("balanced-tree", "[dfs]") {
    btree_node *tree = make_btree_node(10,
                         left(5, leaf(2)),
                         right(15, leaf(20)));

    node* list = dfs(tree);
    REQUIRE(list != NULL);
    node* p = list;
    REQUIRE(p->data == 10); // root
    REQUIRE(p->next != NULL);
    p = p->next;
    REQUIRE(p->data == 5); // left child of root
    REQUIRE(p->next != NULL);
    p = p->next;
    REQUIRE(p->data == 2); // left child of 5
    REQUIRE(p->next != NULL);
    p = p->next;
    REQUIRE(p->data == 15); // right child of root
    REQUIRE(p->next != NULL);
    p = p->next;
    REQUIRE(p->data == 20); // right child of 15
}

TEST_CASE("left-leaning-tree", "[dfs]") {
    btree_node *tree = make_btree_node(30,
                         left(20,
                             left(10, leaf(5))),
                         NULL);

    node* list = dfs(tree);
    REQUIRE(list != NULL);
    node* p = list;
    REQUIRE(p->data == 30); // root
    REQUIRE(p->next != NULL);
    p = p->next;
    REQUIRE(p->data == 20); // left child of root
    REQUIRE(p->next != NULL);
    p = p->next;
    REQUIRE(p->data == 10); // left child of 20
    REQUIRE(p->next != NULL);
    p = p->next;
    REQUIRE(p->data == 5); // left child of 10
}


TEST_CASE("right-leaning-tree", "[dfs]") {
    btree_node *tree = make_btree_node(40,
                         NULL,
                         right(50,
                             right(60, leaf(70))));

    node* list = dfs(tree);
    REQUIRE(list != NULL);
    node* p = list;
    REQUIRE(p->data == 40); // root
    REQUIRE(p->next != NULL);
    p = p->next;
    REQUIRE(p->data == 50); // right child of root
    REQUIRE(p->next != NULL);
    p = p->next;
    REQUIRE(p->data == 60); // right child of 50
    REQUIRE(p->next != NULL);
    p = p->next;
    REQUIRE(p->data == 70); // right child of 60
}


TEST_CASE("mixed-values", "[dfs]") {
    btree_node *tree = make_btree_node(1,
                         make_btree_node(-2,
                             left(3, leaf(-4)),
                             right(5, left(-6, leaf(7)))
                         ),
                         right(8,
                             left(-9,
                                  right(10, left(-11, leaf(12))))
                         )
                      );

    node* list = dfs(tree);
    REQUIRE(list != NULL);
    node* p = list;
    
    REQUIRE(p->data == 1);  // root
    p = p->next;
    REQUIRE(p->data == -2); // left child of root
    p = p->next;
    REQUIRE(p->data == 3);  // left child of -2
    p = p->next;
    REQUIRE(p->data == -4); // left child of 3
    p = p->next;
    REQUIRE(p->data == 5);  // right child of -2
    p = p->next;
    REQUIRE(p->data == -6); // left child of 5
    p = p->next;
    REQUIRE(p->data == 7);  // left child of -6
    p = p->next;
    REQUIRE(p->data == 8);  // right child of root
    p = p->next;
    REQUIRE(p->data == -9); // left child of 8
    p = p->next;
    REQUIRE(p->data == 10); // right child of -9
    p = p->next;
    REQUIRE(p->data == -11);// left child of 10
    p = p->next;
    REQUIRE(p->data == 12); // left child of -11
    p = p->next;

    REQUIRE(p == NULL); // Ensure there are no more nodes
}
