#include "alphabet.h"
#include <cassert>

Alphabet::Alphabet(std::set<Symbol> symbols) {
  assert(!symbols.empty());
  symbols_ = symbols;
}

Alphabet::~Alphabet() {
  symbols_.clear();
}

std::set<Symbol>
Alphabet::getSymbols() {
  return symbols_;
}

void
Alphabet::setSymbols(std::set<Symbol> symbols) {
  symbols_ = symbols;
}