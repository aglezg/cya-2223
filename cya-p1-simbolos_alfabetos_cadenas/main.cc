#include <iostream>
#include "symbol.h"

int main() {
  std::cout << "Hello world\n";
  Symbol symbol1("h");
  std::cout << symbol1.getSymbol() << std::endl;
  return 0;
}