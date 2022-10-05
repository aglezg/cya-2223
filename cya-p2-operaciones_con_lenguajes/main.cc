#include <iostream>

#include "chain.h"
#include <set>

int main(int argc, char* argv[]) {
  Symbol s1("a");
  Symbol s2("c");
  Symbol s3("b");

  std::set<Symbol> set1 = {s1, s2, s3};

  auto it = set1.begin();



/*

  Alphabet alphabet(set1);
  alphabet.print();

  Chain ch1(std::vector<Symbol>({s1, s3}), new Alphabet(set1));

  ch1.print();

  ch1.getAlphabet()->print();
*/
  return 0;
}