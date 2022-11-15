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
* Este archivo contiene el desarrollo de los métodos de la clase Grammar.
*/

#include "../include/grammar.h"

// Constructor
Grammar::Grammar(Symbol initial, Alphabet terminals,
  Alphabet noTerminals, std::set<Production> productions) {
    terminals_ = new Alphabet(terminals.getSymbols());
    noTerminals_ = new Alphabet(noTerminals.getSymbols());
    setInitial(initial);
    setProductions(productions);
}

Grammar::Grammar() {
  terminals_ = nullptr;
  noTerminals_ = new Alphabet({Symbol("S")});
  initial_ = Symbol("S");
  productions_ = {};
}

// Destructor
Grammar::~Grammar() {
  productions_.clear();
}

// Getters
Symbol
Grammar::getInitial() {
  return initial_;
}

Alphabet
Grammar::getTerminals() {
  return *terminals_;
}

Alphabet
Grammar::getNoTerminals() {
  return *noTerminals_;
}

std::set<Production>
Grammar::getProductions() {
  return productions_;
}

// Setters
void
Grammar::setInitial(Symbol initial) {
  initial_ = initial;
  if (!checkInitial()) {
    throw "initial symbol is not a no-terminal symbol.";
  }
}

void
Grammar::setTerminals(Alphabet terminals) {
  terminals_ = new Alphabet(terminals.getSymbols());
  if (!checkInitial()) {
    throw "initial symbol is not a no-terminal symbol.";
  }
  if (!checkProductions()) {
      throw "incorrect productions defined.";
  }
}

void
Grammar::setNoTerminals(Alphabet noTerminals) {
  noTerminals_ = new Alphabet(noTerminals.getSymbols());
  if (!checkProductions()) {
      throw "incorrect productions defined.";
  }
}

void
Grammar::setProductions(std::set<Production> productions) {
  productions_ = productions;
  if (!checkProductions()) {
      throw "incorrect productions defined.";
  }
}

// Comprueba si una producción pertenece a la gramática
bool
Grammar::existProduction(Production p) {
  for (Production prod: productions_) {
    if (prod == p) {
      return true;
    }
  }
  return false;
}

// Añade una producción a la gramática
// Devuelve 'true' si se añadió con éxito
bool
Grammar::addProduction(Production p) {
  if (existProduction(p)) {
    return false;
  } else {
    productions_.insert(p);
    return true;
  }
}

// Elimina una producción de la gramática
// Devuelve 'true' si se eliminó con éxito
bool
Grammar::deleteProduction(Production p) {
  if (existProduction(p)) {
    productions_.erase(p);
    return true;
  } else {
    return false;
  }
}


// Impresión por pantalla
void
Grammar::print() {
  std::cout << "V = " << *noTerminals_ << "\n";
  std::cout << "Alphabet = " << *terminals_ << "\n";
  std::cout << "S = " << initial_ << "\n";
  std::cout << "P(" << productions_.size() << "):\n";
  for (Production p: productions_) {
    std::cout << " ";
    p.print();
    std::cout << "\n";
  }
}

// Comprueba si las producciones son producciones regulares por la derecha
// y están formados por los símbolos terminales y no terminales de la gramática
bool
Grammar::isRightRegular() {
  for (Production p: productions_) {
    if (!noTerminals_->checkSymbol(p.getStart())) {
      return false;
    }
    if (!p.isEmpty()) {
      for (unsigned i = 0; i < p.getGeneration().size() - 1; i++) {
        if (!terminals_->checkSymbol(p.getGeneration()[i])) {
          return false;
        }
      } 
    }
  }
  return true;
}

// Comprueba si las producciones son producciones regulares por la izquierda
// y están formados por los símbolos terminales y no terminales de la gramática
bool
Grammar::isLeftRegular() {
  for (Production p: productions_) {
    if (!noTerminals_->checkSymbol(p.getStart())) {
      return false;
    }
    if (!p.isEmpty()) {
      for (unsigned i = 1; i < p.getGeneration().size(); i++) {
        if (!terminals_->checkSymbol(p.getGeneration()[i])) {
          return false;
        }
      } 
    }
  }
  return true;
}

// Comprueba si una gramática es regular
bool
Grammar::isRegular() {
  return isRightRegular() || isLeftRegular();
}


// Comprueba si el símbolo de arranque se encuentra en el conjunto de símbolos
// no terminales
bool
Grammar::checkInitial() {
  return noTerminals_->checkSymbol(initial_);
}

// Comprueba si las producciones son producciones regulares por la derecha
// y están formados por los símbolos terminales y no terminales de la gramática
bool
Grammar::checkProductions() {
  for (Production p: productions_) {
    if (!noTerminals_->checkSymbol(p.getStart())) {
      return false;
    }
    if (!p.isEmpty()) {
      for (unsigned i = 0; i < p.getGeneration().size(); i++) {
        if (!terminals_->checkSymbol(p.getGeneration()[i]) && !noTerminals_->checkSymbol(p.getGeneration()[i])) {
          return false;
        }
      } 
    }
  }
  return true;
}

// Método de escritura
void
Grammar::write(std::ostream& os) {
  if (terminals_ != nullptr) {
    os << terminals_->getSymbols().size() << "\n";
    for (Symbol symbol: terminals_->getSymbols()) {
      os << symbol << "\n";
    }
  }
  os << noTerminals_->getSymbols().size() << "\n";
  for (Symbol symbol: noTerminals_->getSymbols()) {
    os << symbol << "\n";
  }
  os << initial_ << "\n";
  os << productions_.size() << "\n";
  for (Production p: productions_) {
    os << p << "\n";
  }
}


// Sobrecarga del operador de escritura
std::ostream&
operator<<(std::ostream& os, Grammar& rRg) {
  rRg.write(os);
  return os;
}