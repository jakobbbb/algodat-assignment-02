#ifndef BST_HPP
#define BST_HPP

#include <cstddef>

struct BSTNode {
  int value = 0;
  BSTNode* l = nullptr;
  BSTNode* r = nullptr;
};


class BST {
  public:
    //BST();
    void add(int n);
    std::size_t size() const;
  private:
    std::size_t size_ = 0;
    BSTNode* root_ = nullptr;
    /** Insert child relative to parent. */
    void insert_relative(BSTNode* parent, BSTNode* child);
};

#endif  // BST_HPP
