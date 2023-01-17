/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #02: Operaciones con lenguajes
* @author Adrián González Galván
* @date 13/10/2022
*
* Este archivo contiene el desarrollo de los métodos de la clase Alphabet.
*/

#include "alphabet.h"
#include <cassert>

// Constructor
Alphabet::Alphabet(std::set<Symbol> symbols) {
  setSymbols(symbols);
}

// Destructor
Alphabet::~Alphabet() {
  symbols_.clear();
}

// Getters
std::set<Symbol>
Alphabet::getSymbols() {
  return symbols_;
}

// Setters
void
Alphabet::setSymbols(std::set<Symbol> symbols) {
  assert(!symbols.empty());
  symbols_ = symbols;
}

// Comprueba si un determinado símbolo pertenece al alfabeto
bool
Alphabet::checkSymbol(Symbol symbol) {
  for (Symbol i: symbols_)
    if (i == symbol)
      return true;
  return false;
}

// Añade, si es que no estaba antes, un nuevo símbolo al alfabeto
bool
Alphabet::addSymbol(Symbol symbol) {
  if (checkSymbol(symbol))
    return false;
  else {
    symbols_.insert(symbol);
    return true;
  }
}

// Elimina, si es que existe, un determinado símbolo del alfabeto.
bool
Alphabet::removeSymbol(Symbol symbol) {
  if (checkSymbol(symbol)) {
    symbols_.erase(symbol);
    return true;
  }
  return false;
}

// Impresión por consola de un Alfabeto
void
Alphabet::print() {
  std::cout << "{ ";
  for (Symbol i: symbols_)
    std::cout << i << " ";
  std::cout << "}";
}

// Escritura
void
Alphabet::write(std::ostream& os) {
  os << "{ ";
  for (Symbol i: symbols_)
    os << i << " ";
  os << "}";
}

// Sobrecarga del operador "=="
bool
Alphabet::operator==(Alphabet& alphabet) {
  for (Symbol i: symbols_)
    if (!alphabet.checkSymbol(i))
      return false;
  for (Symbol j: alphabet.getSymbols())
    if(!checkSymbol(j))
      return false;
  return true;
}

// Sobrecarga del operador "+"
Alphabet
Alphabet::operator+(Alphabet& alphabet) {
  Alphabet newAlphabet(getSymbols());
  for (Symbol sym: alphabet.getSymbols())
    newAlphabet.addSymbol(sym);
  return newAlphabet;
}

// Operadores sobrecargados de E/S
std::ostream& operator<<(std::ostream& os, Alphabet& alphabet) {
  alphabet.write(os);
  return os;
}