#include "symbol.h"

Symbol::Symbol(std::string symbol) {
  symbol_ = symbol;
}

Symbol::~Symbol() {}

std::string
Symbol::getSymbol() {
  return symbol_;
}

void
Symbol::setSymbol(std::string symbol) {
  symbol_ = symbol;
} 