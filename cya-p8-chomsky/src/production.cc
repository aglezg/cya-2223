/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #08: Gramáticas en forma normal de Chomsky
* @author Adrián González Galván
* @date 24/11/2022
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

unsigned
Production::getSize() {
  return generation_.size();
}

// Comprueba si es una producción que genera la cadena vacía
bool
Production::isEmpty() {
  return generation_.empty();
}

// Devuelve el simbolo correspondiente a la posición especificada del conjunto
// de símbolos que genera la producción
Symbol&
Production::at(unsigned i) {
  if (i >= generation_.size()) {
    throw "unnacesible symbol position in production ";
  }
  return generation_[i];
}

// Impresión por pantalla
void
Production::print() {
  std::cout << start_ << " -> ";
  if (generation_.empty()) {
    std::cout << kEmptyChainSymbol;
  } else {
    for (Symbol s: generation_) {
    std::cout << s;
    }
  }
}

// Sobrecarga del operador "[]"
Symbol&
Production::operator[](unsigned i){
    if (i >= generation_.size()) {
    throw "unnacesible symbol position in production ";
  }
  return generation_[i];
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

// Lectura
void
Production::read(std::istream& is) {
  std::string reader = "";
  is >> start_;   // start
  is >> reader;   // ->
  Chain chReader;
  is >> chReader; // generation
  generation_ = chReader.getSymbols();
}

// Escritura
void
Production::write(std::ostream& os) {
  os << start_ << " -> ";
  if (generation_.empty()) {
    os << kEmptyChainSymbol;
  } else {
    for (Symbol s: generation_) {
    os << s;
    }
  }
}

// Sobrecarga del operador de lectura
std::istream&
operator>>(std::istream& is, Production& p) {
  p.read(is);
  return is;
}

// Sobrecarga del operador de escritura
std::ostream&
operator<<(std::ostream& os, Production& p) {
  p.write(os);
  return os;
}