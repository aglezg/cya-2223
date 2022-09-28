#include "symbol.h"

Symbol::Symbol(std::string symbol) {
  symbol_ = symbol;
}

Symbol::~Symbol() {}

std::string
Symbol::getSymbol() {
  return symbol_;
}