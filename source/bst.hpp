#ifndef BST_HPP
#define BST_HPP

#include <cstddef>
#include <ostream>

struct BSTNode {
  int value = 0;
  BSTNode* l = nullptr;
  BSTNode* r = nullptr;
  BSTNode* p = nullptr;
};


class BST {
  public:
    /**
     * Insert an integer n to the tree.
     */
    BSTNode* add(int n);
    /**
     * Remove a node from the tree.
     * Returns value of the removed node.
     */
    int remove(BSTNode* n); // TODO
    /**
     * Return pointer to n if it is in the tree.
     */
    BSTNode* search(int n) const;
    BSTNode* search(int n, BSTNode* start) const;
    /**
     * Number of elements in the tree.
     */
    std::size_t size() const;
    /**
     * Smallest element in the tree.
     * Null iff the tree is empty.
     */
    BSTNode* min() const;
    BSTNode* min(BSTNode* start) const;
    /**
     * Largest element in the tree.
     * Null iff the tree is empty.
     */
    BSTNode* max() const;
    BSTNode* max(BSTNode* start) const;
    /**
     * Smallest element larger than n.
     */
    BSTNode* succ(BSTNode* n) const; // TODO
    /**
     * Largest element smaller than n.
     */
    BSTNode* pred(BSTNode* n) const; // TODO
    /**
     * Print tree in dot/graphviz format.
     */
    friend std::ostream& operator<<(std::ostream& o, BST const& b);
    /**
     * Subsitute a node n for a replacement, i. e. change the appropriate child
     * of n's parent to replacement.
     */
    void substitute(BSTNode* n, BSTNode* replacement);
    /**
     * Self-evaulate vallidity
     */
    bool is_valid() const;


  private:
    std::size_t size_ = 0;
    BSTNode* root_ = nullptr;

    /**
     * Insert child relative to parent.
     */
    void insert_relative(BSTNode* parent, BSTNode* child);
    /**
     * Recursively print to o in dot/graphviz format.
     */
    void print(std::ostream& o) const;
    /**
     * Recursively print to o in dot/graphviz format, starting at `start`.
     */
    void print(std::ostream& o, BSTNode* start) const;
    /**
     * Self-evaulate vallidity
     */
    bool is_valid(BSTNode* start) const;
};

/** Print tree in dot/graphviz format. */
std::ostream& operator<<(std::ostream& o, BST const& b);

#endif  // BST_HPP
