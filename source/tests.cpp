#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

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
