#include "chain.h"
#include <cassert>

Chain::Chain(std::vector<Symbol> symbols) {
  alphabet_ = new Alphabet(symbols);
  symbols_ = symbols;
};

Chain::Chain(std::vector<Symbol> symbols, Alphabet* alphabet) {
  alphabet_ = alphabet;
  symbols_ = symbols;
}

bool
Chain::checkChain() {
  
}