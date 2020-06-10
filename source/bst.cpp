#include <cassert>
#include <cstddef>
#include <fstream>
#include <iostream>
#include "bst.hpp"

BST::~BST() {
  while(size() > 0)
    remove(min());
}

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


// adapted from CLRS, p. 296
void BST::substitute(BSTNode* u, BSTNode* v) {
  assert(nullptr != u);

  if (u == root_)
    root_ = v;
  else if (u->p->l == u)  // n is the left child of its parent
    u->p->l = v;
  else
    u->p->r = v;

  if (nullptr != v)
    v->p = u->p;
}


int BST::remove(BSTNode* n) {
  assert(nullptr != n);
  int value = n->value;

  if (nullptr == n->l) {
    substitute(n, n->r);
  } else if (nullptr == n->r) {
    substitute(n, n->l);
  } else {
    auto y = min(n->r);
    if (y->p != n) {
      substitute(y, y->r);
      y->r = n->r;
      y->r->p = y;
    }
    substitute(n, y);
    y->l = n->l;
    n->l->p = y;
  }

  --size_;
  delete n;
  return value;
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
  if (size() == 1) {
    o << "  \"" << root_->value << "\";\n";
  } else {
    print(o, root_);
  }
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

bool BST::is_valid() const {
  return is_valid(root_);
}

bool BST::is_valid(BSTNode* n) const {
  if (nullptr == n) return true;

  if (nullptr != n->l) {
    if (n->l->value < n->value)
      return is_valid(n->l);
    else
      return false;
  }

  if (nullptr != n->r) {
    if (n->r->value > n->value)
      return is_valid(n->r);
    else
      return false;
  }

  return true;
}

void printBST(BST const& b, std::string filename) {
  std::ofstream f;
  f.open(filename);
  f << b;
  f.close();
}
