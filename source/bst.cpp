#include <assert.h>
#include <cstddef>
#include <iostream>
#include "bst.hpp"

void BST::add(int n) {
  if (search(n)) {
    std::cerr << "Not inserting duplicate value " << n << "\n";
    return;
  }
  BSTNode* node = new BSTNode{n};
  if (nullptr == root_) {
    root_ = node;
  } else {
    insert_relative(root_, node);
  }
  ++size_;
}


void BST::insert_relative(BSTNode* parent, BSTNode* child) {
  assert(nullptr != child);
  if (child->value < parent->value) {
    if (nullptr == parent->l)
      parent->l = child;
    else
      insert_relative(parent->l, child);
  } else {
    if (nullptr == parent->r)
      parent->r = child;
    else
      insert_relative(parent->r, child);
  }
}


bool BST::search(int n) {
  return search(n, root_);
}


bool BST::search(int n, BSTNode* start) {
  if (nullptr == start)
    return false;
  if (n == start->value)
    return true;
  if (n < start->value)
    return search(n, start->l);
  else
    return search(n, start->r);
}


std::size_t BST::size() const {
  return size_;
}


std::ostream& operator<<(std::ostream& o, BST const& b) {
  o << "digraph bst {\n";
  b.print(o);
  o << "}\n";
  return o;
}


void BST::print(std::ostream& o) const {
  print(o, root_);
}


void BST::print(std::ostream& o, BSTNode* start) const {
  if (nullptr == start)
    return;

  if (nullptr != start->l) {
    o << "  \"" << start->value << "\" -> \"" << start->l->value << "\";\n";
    print(o, start->l);
  } else if (nullptr != start->r) {
    o << "  \"" << start->value << "\" -> \"nil_" << start->value << "\";\n";
  }

  if (nullptr != start->r) {
    o << "  \"" << start->value << "\" -> \"" << start->r->value << "\";\n";
    print(o, start->r);
  } else if (nullptr != start->l) {
    o << "  \"" << start->value << "\" -> \"nil_" << start->value << "\";\n";
  }
}
