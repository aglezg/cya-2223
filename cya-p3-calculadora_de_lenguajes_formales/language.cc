/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #03: Calculadora de lenguajes formales
* @author Adrián González Galván
* @date 20/10/2022
*
* Este archivo contiene el desarrollo de los métodos de la clase Language.
*/

#include "language.h"

// Constructor
Language::Language(Alphabet* alphabet, std::set<Chain> chains) {
  alphabet_ = alphabet;
  chains_ = chains;
  assert(checkChains());
}

// Destructor
Language::~Language() {
  chains_.clear();
}

// Getters
std::set<Chain>
Language::getChains() {
  return chains_;
}

Alphabet*
Language::getAlphabet() {
  return alphabet_;
}

// Setters
void
Language::setChains(std::set<Chain> chains) {
  chains_ = chains;
}

void
Language::setAlphabet(Alphabet* alphabet) {
  alphabet_ = alphabet;
  assert(checkChains());
}

// Comprueba que cada una de las cadenas se hayan generado a partir
// del correspondiente alfabeto
bool
Language::checkChains() {
  if (!chains_.empty())
    for (Chain chain: chains_)
      if (!checkChain(alphabet_, chain))
        return false;
  return true;
}

// Impresión por pantalla de un lenguaje
void
Language::print() {
  std::cout << *alphabet_ << " { ";
  for (Chain chain: chains_)
    std::cout << chain << " ";
  std::cout << "}";
}

// Comprueba si una cadena pertenece al lenguaje
bool
Language::check(Chain chain) {
  for (Chain i: chains_)
    if (i == chain)
      return true;
  return false;
}

// Añade una cadena al lenguaje
bool
Language::add(Chain chain) {
  if (check(chain))
    return false;
  else {
    chains_.insert(chain);
    return true;
  }
}

// Elimina una cadena del lenguaje
bool
Language::remove(Chain chain) {
  if(!check(chain))
    return false;
  else {
    chains_.erase(chain);
    return true;
  }
}

// Concatena 2 lenguajes de un mismo alfabeto
Language
Language::lConcat(Language language) {
  assert(*alphabet_ == *language.getAlphabet());
  std::set<Chain> concatChains = {};
  for (Chain chain: chains_)
    for (Chain chain2: language.getChains())
      concatChains.insert(chain.concat(chain2));
  return Language(alphabet_, concatChains);
}

// Realiza la potencia de un lenguaje
Language
Language::lPow(unsigned pow) {
  if (pow == 0)
    return Language(alphabet_, std::set<Chain>({Chain(std::vector<Symbol>({}))}));
  else
    return this->lConcat(this->lPow(pow - 1));
}


// Unión de 2 lenguajes
Language
Language::lUnion(Language language) {
  assert(*alphabet_ == *language.getAlphabet());
  std::set<Chain> unionChains = getChains();
  for (Chain i: language.getChains())
    unionChains.insert(i);
  return Language(alphabet_, unionChains);
}

// Intersección de 2 lenguajes
Language
Language::lIntersection(Language language) {
  assert(*alphabet_ == *language.getAlphabet());
  std::set<Chain> intersectionChains = {};
  for (Chain i: chains_)
    if (language.check(i))
      intersectionChains.insert(i);
  return Language(alphabet_, intersectionChains);
}

// Diferencia de 2 lenguajes
Language
Language::lDifference(Language language) {
  assert(*alphabet_ == *language.getAlphabet());
  std::set<Chain> differenceChains = getChains();
  for (Chain i: language.getChains())
    differenceChains.erase(i);
  return Language(alphabet_, differenceChains);
}

// Inversa de un lenguaje
Language
Language::lInverse() {
  std::set<Chain> inverseChains = {};
  for (Chain i: chains_)
    inverseChains.insert(i.inverse());
  return Language(alphabet_, inverseChains);
}

// Lectura
void
Language::read(std::istream& is) {
  std::string my_read = "";
  is >> my_read;
  assert(my_read == "{");

  // Lectura del alfabeto
  std::set<Symbol> alphabetSymbols = {};
  while(my_read != "}") {
    is >> my_read;
    if (my_read != "}") {
      alphabetSymbols.insert(Symbol(my_read));
    }
  }
  alphabet_ = new Alphabet(alphabetSymbols);

  // Lectura de las cadenas
  is >> my_read;
  assert(my_read == "{");
  std::set<Chain> languageChains = {};
  while(my_read != "}") {
    is >> my_read;
    if (my_read != "}") {
      std::string symbolString = "";
      std::vector<Symbol> symbolVector= {};
      for (unsigned i = 0; i < my_read.size(); i++) {
        symbolString += my_read[i];
        if (alphabet_->checkSymbol(Symbol(symbolString))) {
          symbolVector.push_back(Symbol(symbolString));
          symbolString = "";
        }
      }
      if (symbolString != "" && symbolString != kEmptyChainPrint) {
        symbolVector.push_back(Symbol(symbolString));
      }
      languageChains.insert(Chain(symbolVector));
    }
  }

  *this = Language(alphabet_, languageChains);
}

// Escritura
void
Language::write(std::ostream& os) {
  os << *alphabet_ << " { ";
  for (Chain chain: chains_)
    os << chain << " ";
  os << "}";
}

// Sobrecarga del operador <<
std::ostream&
operator<<(std::ostream& os, Language& language) {
  language.write(os);
  return os;
}

// Sobrecarga del operador >>
std::istream&
operator >>(std::istream& is, Language& language) {
  language.read(is);
  return is;
}