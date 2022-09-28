#include <iostream>
#include "symbol.h"

#include <set>

int main() {

  std::set<int> set1;
  set1.insert(22);
  set1.insert(34);
  set1.insert(22);

  std::set<Symbol> set2;

  Symbol symbol1("🤩aa");
  Symbol symbol2("🤩aa");

  set2.insert(symbol1);
  
  std::cout << (symbol1 == symbol2) << std::endl;
  return 0;
}