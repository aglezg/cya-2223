#include <iostream>

#include "symbol.h"
#include <set>

int main(int argc, char* argv[]) {
  Symbol s1("1");
  Symbol s2("2");
  Symbol s3("3");

  bool b1 = "a" > "x";
  std::cout << b1 << std::endl;

  std::set<Symbol> set1 = {s1, s2, s3};

  //Alphabet alphabet(set1);
  //alphabet.print();
  return 0;
}