/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #01: Símbolos, alfabetos y cadenas
* @author Adrián González Galván
* @date 06/10/2022
*
* Este archivo contiene el desarrollo de los métodos de la clase Alphabet.
*/

#include "alphabet.h"
#include <cassert>

// Constructor
Alphabet::Alphabet(std::vector<Symbol> symbols) {
  setSymbols(symbols);
}

// Destructor
Alphabet::~Alphabet() {
  symbols_.clear();
}

// Getters
std::vector<Symbol>
Alphabet::getSymbols() {
  return symbols_;
}

// Setters
void
Alphabet::setSymbols(std::vector<Symbol> symbols) {
  assert(!symbols.empty());
  symbols_ = symbols;
  removeDuplicates();
}

// Comprueba si un determinado símbolo pertenece al alfabeto
bool
Alphabet::checkSymbol(Symbol symbol) {
  for (unsigned i = 0; i < symbols_.size(); i++)
    if (symbols_[i] == symbol)
      return true;
  return false;
}

// Añade, si es que no estaba antes, un nuevo símbolo al alfabeto
bool
Alphabet::addSymbol(Symbol symbol) {
  if (checkSymbol(symbol))
    return false;
  else {
    symbols_.push_back(symbol);
    return true;
  }
}

// Elimina, si es que existe, un determinado símbolo del alfabeto.
bool
Alphabet::removeSymbol(Symbol symbol) {
  if (checkSymbol(symbol)) {
    for (unsigned i = 0; i < symbols_.size(); i++)
      if (symbols_[i] == symbol)
        symbols_.erase(symbols_.begin() + i);
    return true;
  }
  return false;
}

// Impresión por consola de un Alfabeto
void
Alphabet::print() {
  std::cout << "{ ";
  for (unsigned i = 0; i < symbols_.size() - 1; i++)
    std::cout << symbols_[i] << ", ";
  std::cout << symbols_[symbols_.size() - 1] << " }\n";
}

// Escritura
void
Alphabet::write(std::ostream& os) {
  os << "{ ";
  for (unsigned i = 0; i < symbols_.size() - 1; i++)
    os << symbols_[i] << ", ";
  os << symbols_[symbols_.size() - 1] << " }\n";
}

// Elimina los elementos duplicados del alfabeto, en el caso de que los haya
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

// Operadores sobrecargados de E/S
std::ostream& operator<<(std::ostream& os, Alphabet& alphabet) {
  alphabet.write(os);
  return os;
}