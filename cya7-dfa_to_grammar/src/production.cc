/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #07: Gramática regular a partir de un DFA
* @author Adrián González Galván
* @date 17/11/2022
*
* Este archivo contiene el desarrollo de los métodos de la clase Production.
*/

#include "../include/production.h"

// Constructor
Production::Production(Symbol start, std::vector<Symbol> generation) {
  start_ = start;
  generation_ = generation;
}

// Constructor por defecto
Production::Production() {
  start_ = Symbol("S");
  generation_ = {};
}

// Destructor
Production::~Production() {
  generation_.clear();
}

// Getters
Symbol
Production::getStart() {
  return start_;
}

std::vector<Symbol>
Production::getGeneration() {
  return generation_;
}

// Setters
void
Production::setStart(Symbol start) {
  start_ = start;
}

void
Production::setGeneration(std::vector<Symbol> generation) {
  generation_ = generation;
}

// Comprueba si es una producción que genera la cadena vacía
bool
Production::isEmpty() {
  return generation_.empty();
}

// Impresión por pantalla
void
Production::print() {
  std::cout << start_ << " -> ";
  if (generation_.empty()) {
    std::cout << emptyChainSymbol;
  } else {
    for (Symbol s: generation_) {
    std::cout << s;
    }
  }
}

// Sobrecarga del operador '<'
bool
Production::operator<(const Production& p) const {
  if (start_ != p.start_)
    return start_ < p.start_;
  else
    return generation_ < p.generation_;
}

// Sobrecarga del operador "=="
bool
Production::operator==(const Production& p) const {
  if (start_ == p.start_) {
    if (generation_.size() == p.generation_.size()) {
      for (unsigned i = 0; i < generation_.size(); i++) {
        if (generation_[i] != p.generation_[i]) {
          return false;
        }
      }
      return true;
    }
  }
  return false;
}

// Sobrecarga del operadror "!="
bool
Production::operator!=(const Production& p) const {
  return !(*this == p);
}

// Sobrecarga del operador de escritura
void
Production::write(std::ostream& os) {
  os << start_ << " -> ";
  if (generation_.empty()) {
    os << emptyChainSymbol;
  } else {
    for (Symbol s: generation_) {
    os << s;
    }
  }
}

// Sobrecarga del operador de escritura
std::ostream&
operator<<(std::ostream& os, Production& p) {
  p.write(os);
  return os;
}