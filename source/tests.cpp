#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <cstdlib>
#include <iostream>

#include "bst.hpp"

const int nums[] = {8,  11, 3,  36, 28, 16, 35, 34, 38, 32, 31, 21, 37, 14,
                    40, 30, 22, 0,  13, 1,  19, 15, 23, 5,  18, 20, 10, 2,
                    4,  12, 33, 6,  26, 29, 9,  25, 39, 24, 27, 7,  17};

const int nums2[] = {8, 3, 10, 1, 6, 14, 4, 7, 15};

TEST_CASE("node constructor", "[node]") {
  BSTNode n{42};
  REQUIRE(42 == n.value);
  REQUIRE(nullptr == n.l);
  REQUIRE(nullptr == n.r);
}

TEST_CASE("is_valid", "[bst]") {
  GIVEN("a bst") {
    BST b{};
    for (int n : nums2)
      b.add(n);
    REQUIRE(9 == b.size());
    REQUIRE(b.is_valid());
    WHEN("a node is manipulated to invalidate the bst property") {
      auto node = b.search(14);
      node->value = 9;
      REQUIRE(9 == b.size());
      std::cout << b;
      REQUIRE(!b.is_valid());
    }
    WHEN("a node is manipulated but it doesn't invalidate the bst property") {
      auto node = b.search(14);
      node->value = 13;
      REQUIRE(9 == b.size());
      std::cout << b;
      REQUIRE(b.is_valid());
    }
  }
}

TEST_CASE("bst constructor", "[bst]") {
  BST b{};
  REQUIRE(0 == b.size());
  REQUIRE(b.is_valid());
}

SCENARIO("insertion", "[bst]") {
  GIVEN("an empty bst") {
    BST b{};
    REQUIRE(0 == b.size());
    REQUIRE(b.is_valid());
    WHEN("inserting an element") {
      b.add(42);
      REQUIRE(1 == b.size());
      REQUIRE(b.is_valid());
      WHEN("inserting a second element") {
        b.add(1337);
        REQUIRE(2 == b.size());
        REQUIRE(b.is_valid());
        WHEN("inserting a third element") {
          b.add(-8);
          REQUIRE(3 == b.size());
          REQUIRE(b.is_valid());
          WHEN("inserting more elements") {
            for (int n : nums)
              b.add(n);
            REQUIRE(44 == b.size());
            REQUIRE(b.is_valid());
          }
        }
      }
    }
  }
}

SCENARIO("min max", "[bst]") {
  GIVEN("a bst with values from -42 to 42") {
    BST b{};
    for (int n : nums)
      b.add(n);
    REQUIRE(b.is_valid());
    b.add(42);
    REQUIRE(42 == b.max()->value);
    REQUIRE(b.is_valid());
    b.add(-42);
    REQUIRE(-42 == b.min()->value);
    REQUIRE(b.is_valid());
  }
}

SCENARIO("search", "[bst]") {
  BST b{};
  const int nums[] = {8, 11, 3, 36, 28};
  for (int n : nums)
    b.add(n);

  REQUIRE(b.is_valid());

  REQUIRE(b.search(8)->value == 8);
  REQUIRE(b.search(11)->value == 11);
  REQUIRE(b.search(3)->value == 3);
  REQUIRE(b.search(36)->value == 36);
  REQUIRE(b.search(28)->value == 28);

  REQUIRE(nullptr == b.search(9));
  REQUIRE(nullptr == b.search(12));
  REQUIRE(nullptr == b.search(4));
  REQUIRE(nullptr == b.search(37));
  REQUIRE(nullptr == b.search(29));

  REQUIRE(b.is_valid());
}

SCENARIO("print and write", "[bst]") {
  BST b{};
  for (int n : nums)
    b.add(n);
  REQUIRE_NOTHROW(std::cout << b);
  REQUIRE(b.is_valid());
  REQUIRE_NOTHROW(printBST(b, "sample.dot"));
}

#define SUCC(n) b.succ(b.search(n))->value
#define PRED(n) b.pred(b.search(n))->value

SCENARIO("successor and predecessor", "[bst]") {
  GIVEN("a bst") {
    BST b{};
    for (int n : nums2)
      b.add(n);

    // successor
    REQUIRE(3 == SUCC(1));
    REQUIRE(4 == SUCC(3));
    REQUIRE(6 == SUCC(4));
    REQUIRE(7 == SUCC(6));
    REQUIRE(8 == SUCC(7));
    REQUIRE(10 == SUCC(8));
    REQUIRE(14 == SUCC(10));
    REQUIRE(15 == SUCC(14));
    REQUIRE(nullptr == b.succ(b.search(15)));

    // predecessor
    REQUIRE(nullptr == b.pred(b.search(1)));
    REQUIRE(1 == PRED(3));
    REQUIRE(3 == PRED(4));
    REQUIRE(4 == PRED(6));
    REQUIRE(6 == PRED(7));
    REQUIRE(7 == PRED(8));
    REQUIRE(8 == PRED(10));
    REQUIRE(10 == PRED(14));
    REQUIRE(14 == PRED(15));

    REQUIRE(b.is_valid());
  }
}

SCENARIO("delete", "[bst]") {
  GIVEN("a bst") {
    BST b{};
    for (int n : nums2)
      b.add(n);
    auto size_initial = b.size();
    WHEN("deleting node that only has a left child") {
      const int del = 3;
      auto node = b.search(del);
      int val = b.remove(node);
      REQUIRE(del == val);
      REQUIRE(size_initial - 1 == b.size());
      REQUIRE(b.is_valid());
      std::cout << b;
    }
    WHEN("deleting node that only has a right child") {
      const int del = 14;
      auto node = b.search(del);
      int val = b.remove(node);
      REQUIRE(del == val);
      REQUIRE(size_initial - 1 == b.size());
      REQUIRE(b.is_valid());
      std::cout << b;
    }
    WHEN("deleting a leaf") {
      const int del = 1;
      auto node = b.search(del);
      int val = b.remove(node);
      REQUIRE(del == val);
      REQUIRE(size_initial - 1 == b.size());
      REQUIRE(b.is_valid());
      std::cout << b;
    }
    WHEN("deleting the root") {
      const int del = 8;
      auto node = b.search(del);
      int val = b.remove(node);
      REQUIRE(del == val);
      REQUIRE(size_initial - 1 == b.size());
      REQUIRE(b.is_valid());
      std::cout << b;
    }
    WHEN("deleting a node whose right child has a left child") {
      const int del = 3;
      auto node = b.search(del);
      int val = b.remove(node);
      REQUIRE(del == val);
      REQUIRE(size_initial - 1 == b.size());
      REQUIRE(b.is_valid());
      std::cout << b;
    }
  }
}

#define LARGE_TREE_SIZE 1e4
// Note that this is slow only because we're checking validity each time!
SCENARIO("working with a large tree", "[bst]") {
  BST b{};

  /** INSERTION */
  std::srand(0);  // we'll always get the same number sequence
  for (int i = 0; i < LARGE_TREE_SIZE; ++i) {
    auto n = std::rand() - std::rand();
    b.add(n);
    REQUIRE(b.is_valid());
  }
  REQUIRE(b.is_valid());
  auto size_pre = b.size();

  REQUIRE_NOTHROW(printBST(b, "large.dot"));

  /** INVALIDATE THE TREE TO TEST IS_VALID METHOD */
  std::srand(0);
  for (int i = 0; i < LARGE_TREE_SIZE; ++i) {
    auto n = std::rand() - std::rand();
    auto node = b.search(n);
    if (nullptr != node) {
      if (node->p == nullptr)
        continue;
      if (node == node->p->l)
        node->value = node->p->value + 1;
      else
        node->value = node->p->value - 1;
      REQUIRE(!b.is_valid());
      node->value = n;
      REQUIRE(b.is_valid());
    }
  }
  REQUIRE(b.is_valid());

  /** REMOVE ALL NODES */
  std::srand(0);
  for (int i = 0; i < LARGE_TREE_SIZE; ++i) {
    auto n = std::rand() - std::rand();
    auto node = b.search(n);
    if (nullptr != node) {
      b.remove(node);
      REQUIRE(b.is_valid());
    }
  }
  std::cout << "Created a tree with " << size_pre << " elements and deleted "
            << size_pre - b.size() << " of them!\n";
}
