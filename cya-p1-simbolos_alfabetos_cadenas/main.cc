#include <iostream>

#include "symbol.h"
#include "alphabet.h"

int main() {

  Symbol symbol1("b");
  Symbol symbol2("b");
  Symbol symbol3("b");
  Symbol symbol4("e");
  Symbol symbol5("b");
  Symbol symbol0("x");
  std::vector<Symbol> vS = {symbol1, symbol2, symbol3, symbol4, symbol5};
  
  Alphabet alph1(vS);
  std::cout << alph1.addSymbol(symbol0) << std::endl;
  alph1.print();
  
  //std::cout << (symbol1 == symbol2) << std::endl;

  return 0;
}