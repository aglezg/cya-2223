/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #04: Simulación de autómatas finitos
* @author Adrián González Galván
* @date 10/10/2022
*
* Este archivo contiene el desarrollo de los métodos de la clase Symbol.
*/

#include "symbol.h"

// Constructor
Symbol::Symbol(std::string symbol) {
  setSymbol(symbol);
}

// Destructor
Symbol::~Symbol() {}

// Getters
std::string
Symbol::getSymbol() {
  return symbol_;
}

// Setters
void
Symbol::setSymbol(std::string symbol) {
  if (isSubstring(emptyChainSymbol, symbol))
    throw "Symbol cannot contain '&' character";
  symbol_ = symbol;
}

// Sobrecarga del operador "="
Symbol&
Symbol::operator=(Symbol symbol) {
  setSymbol(symbol.getSymbol());
  return *this;
}

// Sobrecarga del operador "=="
bool
Symbol::operator==(Symbol& other) {
  return symbol_ == other.getSymbol();
}

// Sobrecarga del operador "<"
bool Symbol::operator<(const Symbol& symbol) const {
  return symbol_ < symbol.symbol_;
}

// Escritura
void
Symbol::write(std::ostream& os) {
  os << getSymbol();
}

// Lectura
void
Symbol::read(std::istream& is) {
  std::string symbol;
  is >> symbol;
  setSymbol(symbol);
}

// Sobrecarga del operador de escritura
std::ostream&
operator<<(std::ostream& os, Symbol& symbol) {
  symbol.write(os);
  return os;
}

// Sobrecarga del operador de lectura
std::istream&
operator>>(std::istream& is, Symbol& symbol) {
  symbol.read(is);
  return is;
}

// Comprueba si una cadena es subcadena de otra (s2)
bool
isSubstring(std::string s1, std::string s2) {
  int M = s1.length();
  int N = s2.length();
  for (int i = 0; i <= N - M; i++) {
      int j;
      for (j = 0; j < M; j++)
          if (s2[i + j] != s1[j])
              break;
      if (j == M)
          return true;
  }
  return false;
}