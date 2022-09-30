#include <iostream>

#include "symbol.h"
#include "alphabet.h"
#include "chain.h"

int main() {

  Symbol symbol1("1");
  Symbol symbol2("2");
  Symbol symbol3("3");
  Symbol symbol4("4");
  Symbol symbol5("5");
  Symbol symbol0("0");
  Symbol symbolA("A");
  std::vector<Symbol> alpha = {symbol1, symbol2, symbol3, symbol4, symbol5};
  
  //Alphabet alph1(vS);
  //std::cout << alph1.addSymbol(symbol0) << std::endl;
  //alph1.print();

  std::vector<Symbol> chainsym = {symbol1, symbol4, symbol2};
  std::vector<Symbol> chainsym2 = {symbol4, symbol5, symbol5};
  //chainsym.push_back(symbolA);

  Chain chain1(chainsym, new Alphabet(alpha));
  Chain chain2(chainsym2, new Alphabet(alpha));
  chain1.print();
  chain2.print();
  chain2.concat(chain2).inverse().print();
  chain1.inverse().print();
  chain2.inverse().print();
  /*
  std::vector<Chain> chainPre = chain1.suffixes();
  for (unsigned i = 0; i < chain1.suffixes().size(); i ++) {
    chainPre[i].print();
  }
  */
  //std::cout << (symbol1 == symbol2) << std::endl;


  return 0;
}