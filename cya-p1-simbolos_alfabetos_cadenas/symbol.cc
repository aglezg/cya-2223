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

Symbol&
Symbol::operator=(Symbol symbol) {
  setSymbol(symbol.getSymbol());
  return *this;
}

bool
Symbol::operator==(Symbol& other) {
  return symbol_ == other.getSymbol();
}

void
Symbol::write(std::ostream& os) {
  os << getSymbol();
}

std::ostream&
operator<<(std::ostream& os, Symbol& symbol) {
  symbol.write(os);
  return os;
}