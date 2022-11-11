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
* Este archivo contiene el desarrollo de los métodos de la clase rightRegularGrammar.
*/

#include "rightRegularGrammar.h"

// Constructor
RightRegularGrammar::RightRegularGrammar(Symbol initial, Alphabet terminals,
  Alphabet noTerminals, std::set<Production> productions) {
    terminals_ = new Alphabet(terminals.getSymbols());
    noTerminals_ = new Alphabet(noTerminals.getSymbols());
    setInitial(initial);
    setProductions(productions);
}

RightRegularGrammar::RightRegularGrammar() {
  terminals_ = nullptr;
  noTerminals_ = new Alphabet({Symbol("S")});
  initial_ = Symbol("S");
  productions_ = {};
}

// Destructor
RightRegularGrammar::~RightRegularGrammar() {
  productions_.clear();
}

// Getters
Symbol
RightRegularGrammar::getInitial() {
  return initial_;
}

Alphabet
RightRegularGrammar::getTerminals() {
  return *terminals_;
}

Alphabet
RightRegularGrammar::getNoTerminals() {
  return *noTerminals_;
}

std::set<Production>
RightRegularGrammar::getProductions() {
  return productions_;
}

// Setters
void
RightRegularGrammar::setInitial(Symbol initial) {
  initial_ = initial;
  if (!checkInitial()) {
    throw "initial symbol is not a no-terminal symbol.";
  }
}

void
RightRegularGrammar::setTerminals(Alphabet terminals) {
  terminals_ = new Alphabet(terminals.getSymbols());
  if (!checkInitial()) {
    throw "initial symbol is not a no-terminal symbol.";
  }
  if (!checkProductions()) {
      throw "incorrect productions defined.";
  }
}

void
RightRegularGrammar::setNoTerminals(Alphabet noTerminals) {
  noTerminals_ = new Alphabet(noTerminals.getSymbols());
  if (!checkProductions()) {
      throw "incorrect productions defined.";
  }
}

void
RightRegularGrammar::setProductions(std::set<Production> productions) {
  productions_ = productions;
  if (!checkProductions()) {
      throw "incorrect productions defined in the right regular grammar.";
  }
}

// Comprueba si una producción pertenece a la gramática
bool
RightRegularGrammar::checkProduction(Production p) {
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
RightRegularGrammar::addProduction(Production p) {
  if (checkProduction(p)) {
    return false;
  } else {
    productions_.insert(p);
    return true;
  }
}

// Elimina una producción de la gramática
// Devuelve 'true' si se eliminó con éxito
bool
RightRegularGrammar::deleteProduction(Production p) {
  if (checkProduction(p)) {
    productions_.erase(p);
    return true;
  } else {
    return false;
  }
}


// Impresión por pantalla
void
RightRegularGrammar::print() {
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

// Comprueba si el símbolo de arranque se encuentra en el conjunto de símbolos
// no terminales
bool
RightRegularGrammar::checkInitial() {
  return noTerminals_->checkSymbol(initial_);
}

// Comprueba si las producciones son producciones regulares por la derecha
// y están formados por los símbolos terminales y no terminales de la gramática
bool
RightRegularGrammar::checkProductions() {
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

// Método de escritura
void
RightRegularGrammar::write(std::ostream& os) {
  os << terminals_->getSymbols().size() << "\n";
  for (Symbol symbol: terminals_->getSymbols()) {
    os << symbol << "\n";
  }
  os << noTerminals_->getSymbols().size() << "\n";
  for (Symbol symbol: noTerminals_->getSymbols()) {
    os << symbol << "\n";
  }
  os << initial_ << "\n";
  os << productions_.size() << "\n";
  for (Production p: productions_) {
    std::cout << p << "\n";
  }
}


// Sobrecarga del operador de escritura
std::ostream&
operator<<(std::ostream& os, RightRegularGrammar& rRg) {
  rRg.write(os);
  return os;
}