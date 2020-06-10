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
