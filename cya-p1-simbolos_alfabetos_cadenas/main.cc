#include <iostream>
#include "symbol.h"

int main() {
  std::cout << "Hello world\n";
  Symbol symbol1("🤩aa");
  std::cout << symbol1.getSymbol()[0] << std::endl;
  symbol1.setSymbol("y");
  std::cout << symbol1.getSymbol() << std::endl;
  std::string s1 = "h🤩la";
  for (int i = 0; i < s1.size(); i++) {
    std::cout << s1[i] << std::endl;
  }
  return 0;
}