#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <iostream>

#include "bst.hpp"

TEST_CASE("node constructor", "[node]") {
  BSTNode n{42};
  REQUIRE(42 == n.value);
  REQUIRE(nullptr == n.l);
  REQUIRE(nullptr == n.r);
}

TEST_CASE("bst constructor", "[bst]") {
  BST b{};
  REQUIRE(0 == b.size());
}

SCENARIO("insertion", "[bst]") {
  GIVEN("an empty bst") {
    BST b{};
    REQUIRE(0 == b.size());
    WHEN("inserting an element") {
      b.add(4);
      REQUIRE(1 == b.size());
      WHEN("inserting a second element") {
        b.add(3);
        REQUIRE(2 == b.size());
        WHEN("inserting a third element") {
          b.add(5);
          REQUIRE(3 == b.size());
          WHEN("inserting more elements") {
            const int nums[] = {42, 3, 25, -5, 7, 7, 7, 18, 0, 8, 7, -7, 7, 13,
              42, 91, 91, 2, 42, 1, 4, 5, 12, 12, 5, -41, 40, 20, -9, 4, 6};
            for (int n : nums)
              b.add(n);
            REQUIRE(34 == b.size());
          }
        }
      }
    }
  }
}

SCENARIO("search", "[bst]") {
  BST b{};
  const int nums[] = {8, 11, 3, 36, 28};
  for (int n : nums)
    b.add(n);

  REQUIRE(b.search(8));
  REQUIRE(b.search(11));
  REQUIRE(b.search(3));
  REQUIRE(b.search(36));
  REQUIRE(b.search(28));

  REQUIRE(!b.search(9));
  REQUIRE(!b.search(12));
  REQUIRE(!b.search(4));
  REQUIRE(!b.search(37));
  REQUIRE(!b.search(29));
}

SCENARIO("print", "[bst]") {
  BST b{};
  const int nums[] = {8, 11, 3, 36, 28, 16, 35, 34, 38, 32, 31, 21, 37, 14, 40,
    30, 22, 0, 13, 1, 19, 15, 23, 5, 18, 20, 10, 2, 4, 12, 33, 6, 26, 29, 9, 25,
    39, 24, 27, 7, 17};
  for (int n : nums)
    b.add(n);
  REQUIRE_NOTHROW(std::cout << b);
}
