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

// Comprueba si una cadena puede ser generada por la gramática
bool
Grammar::checkChain(Chain chain) {
  Symbol actualProd = getInitial();
  if (isRightRegular()) {
    for (Symbol s: chain.getSymbols()) {
      for (Production p: getProductions()) {
        if (p.getStart() == actualProd  && !p.isEmpty() && p.getGeneration()[0] == s) {
          actualProd = p.getGeneration()[1];
          break;
        }
      }
    }
    for (Production p: getProductions()) {
      if (p.getStart() == actualProd && p.isEmpty()) {
        return true;
      }
    }
    return false;
  } else {
    return false;
  }
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

// Lectura
void
Grammar::read(std::istream& is) {
  std::string nTerminals = "";
  is >> nTerminals;
  if (!is_number(nTerminals) || stoi(nTerminals) < 0) {
    throw "number of terminals specified is Nan or Negative (" +  nTerminals + ")";
  }
  std::set<Symbol> terminals; // Lectura terminales
  for (unsigned i = 0; i < stoi(nTerminals); i++) {
    Symbol symReader;
    is >> symReader;
    terminals.insert(symReader);
  }

  std::string nNoTerminals = "";
  is >> nNoTerminals;
  std::set<Symbol> noTerminals; // Lectura no terminales
  if (!is_number(nNoTerminals) || stoi(nNoTerminals) < 0) {
    throw "number of non terminals specified is Nan or Negative (" +  nNoTerminals + ")";
  }
  for (unsigned i = 0; i < stoi(nNoTerminals); i++) {
    Symbol symReader;
    is >> symReader;
    noTerminals.insert(symReader);
  }
  
  Symbol initial;
  is >> initial; // Lectura del símbolo inicial

  std::string nProductions;
  is >> nProductions;
  std::set<Production> productions; // Lectura de producciones
  if (!is_number(nProductions) || stoi(nProductions) < 0) {
    throw "number of productions specified is Nan or Negative (" +  nNoTerminals + ")";
  }

  for (unsigned i = 0; i < stoi(nProductions); i++) {
    Production prodAux;
    is >> prodAux;
    productions.insert(prodAux);
  }

  *this = Grammar(initial, Alphabet(terminals), Alphabet(noTerminals), productions);
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

// Sobrecarga del operador de lectura
std::istream&
operator>>(std::istream& is, Grammar& grammar) {
  grammar.read(is);
  return is;
}

// Sobrecarga del operador de escritura
std::ostream&
operator<<(std::ostream& os, Grammar& grammar) {
  grammar.write(os);
  return os;
}

