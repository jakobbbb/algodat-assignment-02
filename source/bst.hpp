#ifndef BST_HPP
#define BST_HPP

#include <cstddef>
#include <ostream>

struct BSTNode {
  int value = 0;
  BSTNode* l = nullptr;
  BSTNode* r = nullptr;
};


class BST {
  public:
    void add(int n);
    std::size_t size() const;
    friend std::ostream& operator<<(std::ostream& o, BST const& b);
  private:
    std::size_t size_ = 0;
    BSTNode* root_ = nullptr;
    /** Insert child relative to parent. */
    void insert_relative(BSTNode* parent, BSTNode* child);
    /** Recursively print */
    void print(std::ostream& o) const;
    void print(std::ostream& o, BSTNode* start) const;
};

std::ostream& operator<<(std::ostream& o, BST const& b);

#endif  // BST_HPP
