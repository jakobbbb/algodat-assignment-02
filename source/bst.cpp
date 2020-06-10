#include <assert.h>
#include <cstddef>
#include <iostream>
#include "bst.hpp"

BSTNode* BST::add(int n) {
  BSTNode* node = search(n);
  if (nullptr != node) {
    std::cerr << "Not inserting duplicate value " << n << "\n";
    return node;
  }
  node = new BSTNode{n};
  if (nullptr == root_) {
    root_ = node;
  } else {
    insert_relative(root_, node);
  }
  ++size_;
  return node;
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


BSTNode* BST::search(int n) const {
  return search(n, root_);
}

BSTNode* BST::search(int n, BSTNode* start) const {
  if (nullptr == start || n == start->value)
    return start;
  if (n < start->value)
    return search(n, start->l);
  else
    return search(n, start->r);
}


BSTNode* BST::min() const {
  return min(root_);
}


BSTNode* BST::min(BSTNode* n) const {
  assert(nullptr != n);
  while(nullptr != n->l)
    n = n->l;
  return n;
}


BSTNode* BST::max() const {
  return max(root_);
}


BSTNode* BST::max(BSTNode* n) const {
  assert(nullptr != root_);
  while(nullptr != n->r)
    n = n->r;
  return n;
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
    o << "  \"nil_" << start->value << "\" [shape=point];\n";
    o << "  \"" << start->value << "\" -> \"nil_" << start->value << "\";\n";
  }

  if (nullptr != start->r) {
    o << "  \"" << start->value << "\" -> \"" << start->r->value << "\";\n";
    print(o, start->r);
  } else if (nullptr != start->l) {
    o << "  \"nil_" << start->value << "\" [shape=point];\n";
    o << "  \"" << start->value << "\" -> \"nil_" << start->value << "\";\n";
  }
}
