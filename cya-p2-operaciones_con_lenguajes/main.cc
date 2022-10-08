#include <iostream>

#include "language.h"

int main(int argc, char* argv[]) {
  Symbol s1("a");
  Symbol s2("b");
  Symbol s3("c");

  Symbol x("x");

  std::set<Symbol> set1 = {s1, s2, s3};

  Alphabet alphabet(set1);

  Chain ch1(std::vector<Symbol>({s1, s3}));
  Chain ch2(std::vector<Symbol>({s2, s2}));
  Chain ch3(std::vector<Symbol>({s3, s3, s3, s2, s1}));
  Chain ch4(std::vector<Symbol>({}));

  Chain ch6(std::vector<Symbol>({s1}));
  Chain ch5(std::vector<Symbol>({s2}));

  std::set<Chain> set2 = {ch1, ch2, ch3, ch4};
  std::set<Chain> set3 = {ch4, ch5, ch6, ch3};

  Language l1(new Alphabet(set1), set2);

  std::cout << "l1 = ";
  l1.print();
  std::cout << "\n\n";
  
  Language l2(new Alphabet(set1), set3);

  std::cout << "l2 = ";
  l2.print();
  std::cout << "\n\n";

  std::cout << "Operacion = ";
  l2.lInverse().print();
  std::cout << "\n";

  return 0;
}