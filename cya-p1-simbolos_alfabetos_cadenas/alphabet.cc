#include "alphabet.h"
#include <cassert>

Alphabet::Alphabet(std::vector<Symbol> symbols) {
  setSymbols(symbols);
}

Alphabet::~Alphabet() {
  symbols_.clear();
}

std::vector<Symbol>
Alphabet::getSymbols() {
  return symbols_;
}

void
Alphabet::setSymbols(std::vector<Symbol> symbols) {
  assert(!symbols.empty());
  symbols_ = symbols;
  removeDuplicates();
}

int
Alphabet::checkSymbol(Symbol symbol) {
  for (unsigned i = 0; i < symbols_.size(); i++)
    if (symbols_[i] == symbol)
      return i;
  return -1;
}

bool
Alphabet::addSymbol(Symbol symbol) {
  if (checkSymbol(symbol) != -1)
    return false;
  else {
    symbols_.push_back(symbol);
    return true;
  }
}

bool
Alphabet::removeSymbol(Symbol symbol) {
  int pos = checkSymbol(symbol);
  if (pos != -1) {
    symbols_.erase(symbols_.begin() + pos);
    return true;
  }
  return false;
}

void
Alphabet::print() {
  std::cout << "{ ";
  for (unsigned i = 0; i < symbols_.size() - 1; i++)
    std::cout << symbols_[i] << ", ";
  std::cout << symbols_[symbols_.size() - 1] << " }\n";
}

void
Alphabet::removeDuplicates() {
  for (unsigned i = 0; i < symbols_.size(); i++) {
    for (unsigned j = i + 1; j < symbols_.size(); j++) {
      if (symbols_[i] == symbols_[j]) {
        symbols_.erase(symbols_.begin() + j);
        j--;
      }
    }
  }
}