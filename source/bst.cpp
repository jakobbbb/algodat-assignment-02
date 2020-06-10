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
    if (nullptr == parent->l) {
      child->p = parent;
      parent->l = child;
    } else {
      insert_relative(parent->l, child);
    }
  } else {
    if (nullptr == parent->r) {
      child->p = parent;
      parent->r = child;
    } else {
      insert_relative(parent->r, child);
    }
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


// CLRS, p. 292
BSTNode* BST::succ(BSTNode* n) const {
  if (nullptr != n->r)
    return min(n->r);
  auto y = n->p;
  while(nullptr != y && n == y->r) {
    n = y;
    y = y->p;
  }
  return y;
}


// adapted from CLRS, p. 292
BSTNode* BST::pred(BSTNode* n) const {
  if (nullptr != n->l)
    return max(n->l);
  auto y = n->p;
  while(nullptr != y && n == y->l) {
    n = y;
    y = y->p;
  }
  return y;
}


void BST::substitute(BSTNode* n, BSTNode* replacement) {
  assert(nullptr != n);
  assert(nullptr != n->p);
  assert(nullptr != replacement);
  if (n == root_) {
    root_ = replacement;
    replacement->p = nullptr;
  } else if (n->p->l == n) { // n is the left child of its parent
    n->p->l = replacement;
    replacement->p = n->p;
  } else if (n->p->r == n) { // n is the right child of its parent
    n->p->r = replacement;
    replacement->p = n->p;
  }
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
