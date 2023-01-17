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
* Este archivo contiene el desarrollo de los métodos de la clase ContextFreeGrammar.
*/

#include "../include/contextFreeGrammar.h"

// Constructor
ContextFreeGrammar::ContextFreeGrammar(Symbol initial, Alphabet terminals,
  Alphabet noTerminals, std::set<Production> productions) {
    terminals_ = new Alphabet(terminals.getSymbols());
    noTerminals_ = new Alphabet(noTerminals.getSymbols());
    setInitial(initial);
    setProductions(productions);
}

ContextFreeGrammar::ContextFreeGrammar() {
  terminals_ = nullptr;
  noTerminals_ = new Alphabet({Symbol("S")});
  initial_ = Symbol("S");
  productions_ = {};
}

// Destructor
ContextFreeGrammar::~ContextFreeGrammar() {
  productions_.clear();
}

// Getters
Symbol
ContextFreeGrammar::getInitial() {
  return initial_;
}

Alphabet
ContextFreeGrammar::getTerminals() {
  return *terminals_;
}

Alphabet
ContextFreeGrammar::getNoTerminals() {
  return *noTerminals_;
}

std::set<Production>
ContextFreeGrammar::getProductions() {
  return productions_;
}

// Setters
void
ContextFreeGrammar::setInitial(Symbol initial) {
  initial_ = initial;
  if (!checkInitial()) {
    throw "initial symbol is not a no-terminal symbol.";
  }
}

void
ContextFreeGrammar::setTerminals(Alphabet terminals) {
  terminals_ = new Alphabet(terminals.getSymbols());
  if (!checkInitial()) {
    throw "initial symbol is not a no-terminal symbol.";
  }
  if (!checkProductions()) {
      throw "incorrect productions defined.";
  }
}

void
ContextFreeGrammar::setNoTerminals(Alphabet noTerminals) {
  noTerminals_ = new Alphabet(noTerminals.getSymbols());
  if (!checkProductions()) {
      throw "incorrect productions defined.";
  }
}

void
ContextFreeGrammar::setProductions(std::set<Production> productions) {
  productions_ = productions;
  if (!checkProductions()) {
      throw "incorrect productions defined.";
  }
}

// Comprueba si una producción pertenece a la gramática
bool
ContextFreeGrammar::existProduction(Production p) {
  for (Production prod: productions_) {
    if (prod == p) {
      return true;
    }
  }
  return false;
}

// Comprueba si existe un simbolo no terminal en la gramática
bool
ContextFreeGrammar::existNonTerminal(Symbol s) {
  return noTerminals_->checkSymbol(s);
}

// Añade una producción a la gramática
// Devuelve 'true' si se añadió con éxito
bool
ContextFreeGrammar::addProduction(Production p) {
  if (existProduction(p)) {
    return false;
  } else {
    productions_.insert(p);
    return true;
  }
}

// Añade, si no existe, un nuevo no terminal
bool
ContextFreeGrammar::addNonTerminal(Symbol s) {
  return noTerminals_->addSymbol(s);
}

// Elimina una producción de la gramática
// Devuelve 'true' si se eliminó con éxito
bool
ContextFreeGrammar::deleteProduction(Production p) {
  if (existProduction(p)) {
    productions_.erase(p);
    return true;
  } else {
    return false;
  }
}

// Elimina un simbolo no terminal de la gramática
// Para ello se debe comprobar que dicho símbolo no se use en ninguna
// producción
bool
ContextFreeGrammar::deleteNonTerminal(Symbol s) {
  for (Production p: productions_) {
    if (p.getStart() == s) {
      throw "noTerminal symbol cant be deleted";
    }
    for (Symbol symbol: p.getGeneration()) {
      if (symbol == s) {
        throw "noTerminal symbol cant be deleted";
      }
    }
  }
  return noTerminals_->removeSymbol(s);
}

// Genera una gramática independiente del contexto en forma normal de Chomsky
ContextFreeGrammar
ContextFreeGrammar::toChomsky() {

  if (hasEmptyProductions() || hasUnitProductions()) {
    throw "the grammar cant be written as chomsky form";
  }
  
  ContextFreeGrammar resultGrammar(initial_, *terminals_, *noTerminals_);
  std::set<Production> productions = productions_;

  for (Production p: productions_) { // Primera fase
    if (p.getSize() >= 2) {
      std::vector<Symbol> newGeneration = {};
      for (Symbol s: p.getGeneration()) {
        if (terminals_->checkSymbol(s)){
          Symbol symbolAux("C" + s.getSymbol());
          productions.insert(Production(symbolAux, {s}));
          newGeneration.push_back(symbolAux);
          resultGrammar.addNonTerminal(symbolAux);
        } else {     
          newGeneration.push_back(s);
        }
      }
      Production newProd(p.getStart(), newGeneration);
      productions.insert(newProd);
      productions.erase(p);
    }
  }

  std::set<Production> productions2 = productions;
  unsigned prodLetter = 3;

  for (Production p: productions) { // Segunda fase
    if (p.getSize() >= 3) {
      std::vector<Symbol> newGeneration = p.getGeneration();
      for (unsigned i = p.getSize() - 2; i >= 1; i--) {
        Symbol symbolAux(kCapitalLetters[prodLetter] + std::to_string(i));
        productions2.insert(Production(symbolAux,
          {newGeneration[newGeneration.size() - 2],
          newGeneration[newGeneration.size() - 1]}));
        resultGrammar.addNonTerminal(symbolAux);
        newGeneration.pop_back();
        newGeneration.pop_back();
        newGeneration.push_back(symbolAux);
      }
      Production newProd(p.getStart(), newGeneration);
      productions2.insert(newProd);
      productions2.erase(p);
      prodLetter = (prodLetter + 1) % kCapitalLetters.size();
    }
  }

  resultGrammar.setProductions(productions2);
  return resultGrammar;
}

// Impresión por pantalla
void
ContextFreeGrammar::print() {
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
ContextFreeGrammar::isRightRegular() {
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
ContextFreeGrammar::isLeftRegular() {
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
ContextFreeGrammar::isRegular() {
  return isRightRegular() || isLeftRegular();
}

// Comprueba si tiene producciones vacías
bool
ContextFreeGrammar::hasEmptyProductions() {
  for (Production p: productions_) {
    if (p.isEmpty() && p.getStart() != initial_) {
      return true;
    }
  }
  return false;
}

// Comprueba si tiene producciones unitarias
bool
ContextFreeGrammar::hasUnitProductions() {
  for (Production p: productions_) {
    if (p.getGeneration().size() == 1 && noTerminals_->checkSymbol(p.getGeneration()[0])) {
      return true;
    }
  }
  return false;
}


// Comprueba si una cadena puede ser generada por la gramática
bool
ContextFreeGrammar::checkChain(Chain chain) {
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
ContextFreeGrammar::checkInitial() {
  return noTerminals_->checkSymbol(initial_);
}

// Comprueba si las producciones son producciones regulares por la derecha
// y están formados por los símbolos terminales y no terminales de la gramática
bool
ContextFreeGrammar::checkProductions() {
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
ContextFreeGrammar::read(std::istream& is) {
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

  *this = ContextFreeGrammar(initial, Alphabet(terminals), Alphabet(noTerminals), productions);
}

// Método de escritura
void
ContextFreeGrammar::write(std::ostream& os) {
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
operator>>(std::istream& is, ContextFreeGrammar& ContextFreeGrammar) {
  ContextFreeGrammar.read(is);
  return is;
}

// Sobrecarga del operador de escritura
std::ostream&
operator<<(std::ostream& os, ContextFreeGrammar& ContextFreeGrammar) {
  ContextFreeGrammar.write(os);
  return os;
}

