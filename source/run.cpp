#include <iostream>

#include "bst.hpp"

int main() {
  std::string cmd = "h";
  BST b{};
  while (cmd != "q" && !cmd.empty()) {
    if (cmd == "h") {
      std::cout << "Available Commands:\n";
      std::cout << "\th\tshow help\n";
      std::cout << "\ta\tadd to tree\n";
      std::cout << "\ts\tsearch in tree\n";
      std::cout << "\tr\tremove from tree\n";
      std::cout << "\tpd\tprint predecessor\n";
      std::cout << "\tsc\tprint successor\n";
      std::cout << "\tmin\tprint minimum\n";
      std::cout << "\tmax\tprint maximum\n";
      std::cout << "\tp\tprint tree to file (- for stdout)\n";
      std::cout << "\tsize\tprint size\n";
      std::cout << "\tq\tquit\n";
    }
    if (cmd == "a") {
      std::cout << "enter a number to add: ";
      int n;
      std::cin >> n;
      b.add(n);
    }
    if (cmd == "s") {
      std::cout << "enter a number to search: ";
      int n;
      std::cin >> n;
      if (nullptr == b.search(n))
        std::cout << "not found\n";
      else
        std::cout << "found\n";
    }
    if (cmd == "r") {
      std::cout << "enter a number to remove: ";
      int n;
      std::cin >> n;
      auto node = b.search(n);
      if (nullptr != node)
        b.remove(node);
      else
        std::cout << "not in tree!\n";
    }
    if (cmd == "pd" || cmd == "sc") {
      std::string what = cmd == "pd" ? "predecessor" : "successor";
      std::cout << "enter a number to find " << what << " of: ";
      int n;
      std::cin >> n;
      BSTNode* node = b.search(n);
      if (nullptr == node) {
        std::cout << "not found\n";
      } else {
        auto node_what = cmd == "pd" ? b.pred(node) : b.succ(node);
        if (nullptr == node_what) {
          std::cout << "No " << what << " found\n";
        } else {
          std::cout << what << ": " << node_what->value << "\n";
        }
      }
    }
    if (cmd == "min" || cmd == "max") {
      std::string what = cmd == "min" ? "minimum" : "maximum";
      BSTNode* node_what = cmd == "min" ? b.min() : b.max();
      if (nullptr == node_what) {
          std::cout << "No " << what << " found\n";
      } else {
          std::cout << what << ": " << node_what->value << "\n";
      }
    }
    if (cmd == "p") {
      std::cout << "enter a filename (- for stdout): ";
      std::string fname;
      std::cin >> fname;
      if (fname == "-")
        std::cout << b;
      else
        printBST(b, fname);
    }
    if (cmd == "size") {
      std::cout << "tree contains " << b.size() << " elements\n";
    }
    std::cout << "command? ";
    std::cin >> cmd;
  }
  std::cout << "Goodbye :)\n";
  return 0;
}
