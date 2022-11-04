/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #04: Simulación de autómatas finitos
* @author Adrián González Galván
* @date 10/10/2022
*
* Este archivo contiene el desarrollo de los métodos de la clase Chain.
*/

#include "chain.h"
#include <cassert>

// Constructor
Chain::Chain(std::vector<Symbol> symbols) {
  symbols_ = symbols;
};

// Constructor por defecto
Chain::Chain() {
  std::vector<Symbol> symbols = {};
  symbols_ = symbols;
}

// Destructor
Chain::~Chain() {
  symbols_.clear();
}

// Getters
std::vector<Symbol>
Chain::getSymbols() {
  return symbols_;
}

// Setters
void
Chain::setSymbols(std::vector<Symbol> symbols) {
  symbols_ = symbols;
}


// Calcula la longitud de la cadena
unsigned
Chain::length() {
  return symbols_.size();
}

// Calcula la cadena inversa de la cadena
Chain
Chain::inverse() {
  if (length() == 0)
    return *this;
  else {
    Symbol auxiliar = getSymbols().front();
    std::vector<Symbol> chain_symbols_without_aux = {};
    for (unsigned i = 1; i < length(); i++)
      chain_symbols_without_aux.push_back(getSymbols()[i]);
    return Chain(chain_symbols_without_aux).inverse().concat(Chain({auxiliar}));
  }
}

// Concatena una cadena con otra
Chain
Chain::concat(Chain chain) {
  std::vector<Symbol> new_symbols = getSymbols();
  for (unsigned i = 0; i < chain.length(); i++) {
    new_symbols.push_back(chain.getSymbols()[i]);
  }
  return Chain(new_symbols);
}

// Calcula las cadenas prefijos de la misma cadena
std::set<Chain>
Chain::prefixes() {
  std::set<Chain> chainPrefixes = {Chain()};
  std::vector<Symbol> symbolsCopy; 
  for (unsigned i = 0; i < this->length(); i++) {
    symbolsCopy.push_back(getSymbols()[i]);
    chainPrefixes.insert(Chain(symbolsCopy));
  }
  return chainPrefixes;
}

// Calcula las cadenas sufijos de la misma cadena
std::set<Chain>
Chain::suffixes() {
  std::set<Chain> chainSuffixes = {Chain()};
  std::vector<Symbol> symbolsCopy = getSymbols(); 
  for (int i = this->length() - 1; i >= 0; i--) {
    chainSuffixes.insert(Chain(symbolsCopy));
    symbolsCopy.erase(symbolsCopy.begin());
  }
  return chainSuffixes;
}

// Calcula las subcadenas de la misma cadena
std::set<Chain>
Chain::substrings() {
  std::set<Chain> chainSubstrings = {Chain()};
  
  int substrings_size = 1;
  while (substrings_size <= length()) {
    for (unsigned i = 0; i <= length() - substrings_size; i++) {
      std::vector<Symbol> symbolsCopy = {};
      for (unsigned j = i; j < i + substrings_size; j++)
        symbolsCopy.push_back(getSymbols()[j]);
      chainSubstrings.insert(Chain(symbolsCopy));
    }
    substrings_size++;
  }
  return chainSubstrings;
}

// Comprueba si una cadena es palíndroma
bool
Chain::isPalindrome() {
  Chain inverseChain = this->inverse();
  return *this == inverseChain;
}

// Impresión por pantalla
void
Chain::print() {
  if (getSymbols().empty()) {
    std::cout << emptyChainSymbol << std::endl;
  } else {
    for (unsigned i = 0; i < length(); i++)
      std::cout << getSymbols()[i];
    std::cout << "\n";
  }
}

// Sobrecarga del operador "=="
bool
Chain::operator==(Chain& chain) {
  if (length() != chain.length())
    return false;
  for (unsigned i = 0; i < length(); i++)
    if (getSymbols()[i] != chain.getSymbols()[i])
      return false;
  return true;
}

// Sobrecarga del operador "<"
bool Chain::operator<(const Chain& chain) const {
  return symbols_ < chain.symbols_;
}

// Escritura
void
Chain::write(std::ostream& os) {
  if (getSymbols().empty())
    os << emptyChainSymbol;
  else
    for (unsigned i = 0; i < length(); i++)
      os << getSymbols()[i];
}

// Lectura
void
Chain::read(std::istream& is) {
  std::string my_chain = "";
  is >> my_chain;
  if (my_chain == emptyChainSymbol) {
    *this = Chain();
  } else {
    std::vector<Symbol> chainSymbols;
    for (unsigned i = 0; i < my_chain.length(); i++)
      chainSymbols.push_back(Symbol(std::string(1, my_chain[i])));
    *this = Chain(chainSymbols);
  }
}

// Comprueba si una determinada cadena está formada con símbolos de un
// determinado alfabeto
bool
Chain::belongsToAlphabet(Alphabet alphabet) {
  for (unsigned i = 0; i < length(); i++)
    if (!alphabet.checkSymbol(getSymbols()[i]))
        return false;
  return true;
}

// Sobrecarga del operador de lectura
std::istream&
operator>>(std::istream& is, Chain& chain) {
  chain.read(is);
  return is;
}

// Sobrecarga del operador de escritura
std::ostream&
operator<<(std::ostream& os, Chain& chain) {
  chain.write(os);
  return os;
}

// Comprueba si un elemento pertenece a un determinado vector
template <class T>
bool
include(std::vector<T> v, T element) {
  for(unsigned i = 0; i < v.size(); i++)
    if (v[i] == element)
      return true;
  return false;
}