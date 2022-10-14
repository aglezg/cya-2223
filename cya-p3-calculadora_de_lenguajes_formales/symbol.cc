/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #01: Símbolos, alfabetos y cadenas
* @author Adrián González Galván
* @date 13/10/2022
*
* Este archivo contiene el desarrollo de los métodos de la clase Symbol.
*/

#include "symbol.h"

// Constructor
Symbol::Symbol(std::string symbol) {
  symbol_ = symbol;
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
Symbol::operator==(const  Symbol& symbol) {
  return symbol_ == symbol.symbol_;
}

// Sobrecarga del operador ">"
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
  is >> symbol_;
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