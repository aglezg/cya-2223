#include "chain.h"
#include <cassert>

Chain::Chain(std::vector<Symbol> symbols) {
  alphabet_ = new Alphabet(symbols);
  symbols_ = symbols;
};

Chain::Chain(std::vector<Symbol> symbols, Alphabet* alphabet) {
  alphabet_ = alphabet;
  symbols_ = symbols;
  assert(checkChain());
}

Chain::~Chain() {
  symbols_.clear();
}

std::vector<Symbol>
Chain::getSymbols() {
  return symbols_;
}

Alphabet*
Chain::getAlphabet() {
  return alphabet_;
}

unsigned
Chain::length() {
  return symbols_.size();
}

Chain
Chain::inverse() {

  if (length() == 0)
    return *this;
  else {
    Symbol auxiliar = getSymbols().front();
    std::vector<Symbol> chain_symbols_without_aux = {};
    for (unsigned i = 1; i < length(); i++)
      chain_symbols_without_aux.push_back(getSymbols()[i]);
    return Chain(chain_symbols_without_aux, getAlphabet()).inverse().concat(Chain({auxiliar}));
  }

}

Chain
Chain::concat(Chain chain) {
  std::vector<Symbol> new_symbols = getSymbols();
  for (unsigned i = 0; i < chain.length(); i++) {
    new_symbols.push_back(chain.getSymbols()[i]);
  }
  return Chain(new_symbols);
}

std::vector<Chain>
Chain::prefixes() {
  std::vector<Chain> chainPrefixes = {Chain({}, alphabet_)};
  std::vector<Symbol> symbolsCopy; 
  for (unsigned i = 0; i < this->length(); i++) {
    symbolsCopy.push_back(getSymbols()[i]);
    chainPrefixes.push_back(Chain(symbolsCopy, alphabet_));
  }
  return chainPrefixes;
}

std::vector<Chain>
Chain::suffixes() {
  std::vector<Chain> chainSuffixes = {};
  std::vector<Symbol> symbolsCopy = getSymbols(); 
  for (int i = this->length() - 1; i >= 0; i--) {
    chainSuffixes.push_back(Chain(symbolsCopy, alphabet_));
    symbolsCopy.erase(symbolsCopy.begin());
  }
  chainSuffixes.push_back(Chain({}, alphabet_));
  return chainSuffixes;
}

bool
Chain::checkChain() {
  bool check = true;
  for (unsigned i = 0; i < symbols_.size(); i++) {
    for (unsigned j = 0; j < alphabet_->getSymbols().size(); j++)
      if (symbols_[i] == alphabet_->getSymbols()[j]) {
        check = true;
        break;
      } else {
        check = false;
      }
    if (!check) return false;
    }
  return true;
}

void
Chain::print() {
  if (getSymbols().empty()) {
    std::cout << '&' << std::endl;
  } else {
    for (unsigned i = 0; i < length(); i++)
      std::cout << getSymbols()[i];
    std::cout << "\n";
  }
}