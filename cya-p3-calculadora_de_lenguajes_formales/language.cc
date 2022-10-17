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

// Constructor sin alfabeto
Language::Language(std::set<Chain> chains) {
  chains_ = chains;
  if (chains.empty()) {
    alphabet_ = new Alphabet(std::set<Symbol>({Symbol(".")}));
  } else {
    std::set<Symbol> alphabetSymbols = {};
    for (Chain chain: chains)
      for (unsigned i = 0; i < chain.length(); i++)
        alphabetSymbols.insert(chain.getSymbols()[i]);
    if (!alphabetSymbols.empty())
      alphabet_ = new Alphabet(alphabetSymbols);
    else
      alphabet_ = new Alphabet(std::set<Symbol>({Symbol(".")}));
  }
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
  std::set<Symbol> newAlphabet = alphabet_->getSymbols();
  for (Symbol sym: language.getAlphabet()->getSymbols())
    newAlphabet.insert(sym);
  std::set<Chain> concatChains = {};
  for (Chain chain: chains_)
    for (Chain chain2: language.getChains())
      concatChains.insert(chain.concat(chain2));
  return Language(new Alphabet(newAlphabet), concatChains);
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
  std::set<Symbol> newAlphabet = alphabet_->getSymbols();
  for (Symbol sym: language.getAlphabet()->getSymbols())
    newAlphabet.insert(sym);  std::set<Chain> unionChains = getChains();
  for (Chain i: language.getChains())
    unionChains.insert(i);
  return Language(new Alphabet(newAlphabet), unionChains);
}

// Intersección de 2 lenguajes
Language
Language::lIntersection(Language language) {
  std::set<Symbol> newAlphabet = alphabet_->getSymbols();
  for (Symbol sym: language.getAlphabet()->getSymbols())
    newAlphabet.insert(sym);
  std::set<Chain> intersectionChains = {};
  for (Chain i: chains_)
    if (language.check(i))
      intersectionChains.insert(i);
  return Language(new Alphabet(newAlphabet), intersectionChains);
}

// Diferencia de 2 lenguajes
Language
Language::lDifference(Language language) {
  std::set<Symbol> newAlphabet = alphabet_->getSymbols();
  for (Symbol sym: language.getAlphabet()->getSymbols())
    newAlphabet.insert(sym);
  std::set<Chain> differenceChains = getChains();
  for (Chain i: language.getChains())
    differenceChains.erase(i);
  return Language(new Alphabet(newAlphabet), differenceChains);
}

// Inversa de un lenguaje
Language
Language::lInverse() {
  std::set<Chain> inverseChains = {};
  for (Chain i: chains_)
    inverseChains.insert(i.inverse());
  return Language(alphabet_, inverseChains);
}

// Todas las subcadenas de un lenguaje
Language
Language::subStrings() {
  std::set<Chain> subStringsChains = chains_;
  for (Chain i: chains_) {
    std::vector<Chain> substringsChaini = i.substrings();
    for (unsigned i = 0; i < substringsChaini.size(); i++)
      subStringsChains.insert(substringsChaini[i]);
  }
  return Language(alphabet_, subStringsChains);
}

// Sobrecarga del operador '>'
bool
Language::operator<(const Language& language) const {
  return chains_ < language.chains_;
}

// Lectura
void
Language::read(std::istream& is) {
  std::string my_read = "";

  std::vector<Symbol> symbolVector = {};
  std::set<Chain> languageChains = {};

  bool isEmptyLanguage = true;

  // Lectura de las cadenas
  char character = '.';
  while (character != kClosingLanguage) {
    is.get(character);
    if (character != ' ' && character != kOpenningLanguage && 
      character != kChainSeparator && character != kClosingLanguage
      && character != kEmptyChain) {
      std::string symbolString(1, character);
      symbolVector.push_back(Symbol(symbolString));
      isEmptyLanguage = false;
    } else if(character == kEmptyChain) {
      isEmptyLanguage = false;
    } else if (character == kChainSeparator || character == kClosingLanguage) {
      if (!isEmptyLanguage)
        languageChains.insert(Chain(symbolVector));
      symbolVector.clear();
    }
  }
  *this = Language(languageChains);
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

// Comprueba si una string es un operador de lenguaje
bool
isLanguageOperation(std::string op) {
  return op == kConcatOp || op == kUnionOp || op == kIntersectionOp ||
    op == kDifferenceOp || op == kInverseOP;
}

// Realiza una operación polaca de lenguajes empleando para ello una pila.
// Devuelve 'true' si la operación se ejecutó correctamente.
bool
operateLanguageStack(std::stack<Language>& languageStack, std::string op) {
  if (isLanguageOperation(op) && !languageStack.empty()) {
    Language l2 = languageStack.top();
    languageStack.pop();
    if (op == kConcatOp) {
      if (languageStack.empty())
        return false;
      Language l1 = languageStack.top();
      languageStack.pop();
      languageStack.push(l1.lConcat(l2));
    } else if (op == kUnionOp) {
      if (languageStack.empty())
        return false;
      Language l1 = languageStack.top();
      languageStack.pop();
      languageStack.push(l1.lUnion(l2));
    } else if (op == kIntersectionOp) {
      if (languageStack.empty())
        return false;
      Language l1 = languageStack.top();
      languageStack.pop();
      languageStack.push(l1.lIntersection(l2));
    } else if (op == kDifferenceOp) {
      if (languageStack.empty())
        return false;
      Language l1 = languageStack.top();
      languageStack.pop();
      languageStack.push(l1.lDifference(l2));
    } else if (op == kInverseOP) {
      languageStack.push(l2.lInverse());
    }
  }
  return isLanguageOperation(op);
}