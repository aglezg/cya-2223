/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #01: Símbolos, alfabetos y cadenas
* @author Adrián González Galván
* @date _/_/2022
*
* Este archivo contiene el desarrollo de los métodos de la clase Chain.
*/

#include "chain.h"
#include <cassert>

// Constructor sin especificar alfabeto
Chain::Chain(std::vector<Symbol> symbols) {
  alphabet_ = new Alphabet(symbols);
  symbols_ = symbols;
};

// Constructor especificando el alfabeto
Chain::Chain(std::vector<Symbol> symbols, Alphabet* alphabet) {
  alphabet_ = alphabet;
  symbols_ = symbols;
  assert(checkChain());
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

Alphabet*
Chain::getAlphabet() {
  return alphabet_;
}

// Setters
void
Chain::setSymbols(std::vector<Symbol> symbols) {
  symbols_ = symbols;
  assert(checkChain());
}

void
Chain::setAlphabet(Alphabet* alphabet) {
  alphabet_ = alphabet;
  assert(checkChain());
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
    return Chain(chain_symbols_without_aux, getAlphabet()).inverse().concat(Chain({auxiliar}));
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
std::vector<Chain>
Chain::prefixes() {
  std::vector<Chain> chainPrefixes = {Chain({}, alphabet_)};
  std::vector<Symbol> symbolsCopy; 
  for (unsigned i = 0; i < this->length(); i++) {
    symbolsCopy.push_back(getSymbols()[i]);
    chainPrefixes.push_back(Chain(symbolsCopy, alphabet_));
  }
  return chainPrefixes;
}

// Calcula las cadenas sufijos de la misma cadena
std::vector<Chain>
Chain::suffixes() {
  std::vector<Chain> chainSuffixes = {};
  std::vector<Symbol> symbolsCopy = getSymbols(); 
  for (int i = this->length() - 1; i >= 0; i--) {
    chainSuffixes.push_back(Chain(symbolsCopy, alphabet_));
    symbolsCopy.erase(symbolsCopy.begin());
  }
  chainSuffixes.push_back(Chain({}, alphabet_));
  return chainSuffixes;
}


// Calcula las subcadenas de la misma cadena
std::vector<Chain>
Chain::substrings() {
  std::vector<Chain> chainSubstrings = {Chain(std::vector<Symbol>({}), alphabet_)};
  
  int substrings_size = 1;
  while (substrings_size <= length()) { // bien
    for (unsigned i = 0; i <= length() - substrings_size; i++) {
      std::vector<Symbol> symbolsCopy = {};
      for (unsigned j = i; j < i + substrings_size; j++)
        symbolsCopy.push_back(getSymbols()[j]);
      if (!include(chainSubstrings, Chain(symbolsCopy, alphabet_)))
        chainSubstrings.push_back(Chain(symbolsCopy, alphabet_));
    }
    substrings_size++;
  }
  return chainSubstrings;
}

// Impresión por pantalla
void
Chain::print() {
  if (getSymbols().empty()) {
    std::cout << kEmptyChain << std::endl;
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
    if (getSymbols()[i].getSymbol() != chain.getSymbols()[i].getSymbol())
      return false;
  return true;
}

// Escritura
void
Chain::write(std::ostream& os) {
  if (getSymbols().empty())
    os << kEmptyChain;
  else
    for (unsigned i = 0; i < length(); i++)
      os << getSymbols()[i];
}

// Lectura
void
Chain::read(std::istream& is) {
  std::string my_line = "";
  std::getline (is, my_line);
  std::vector<std::string> divided_line = stringToVector(my_line);
  
  // Extraemos cadena
  std::string chainSymbolsString = divided_line.back();
  divided_line.pop_back();

  std::vector<Symbol> chainSymbols= {};
  for (unsigned i = 0; i < chainSymbolsString.size(); i++) {
    std::string str;
    str += chainSymbolsString[i];
    chainSymbols.push_back(Symbol(str));
  }

  // Extraemos el alfabeto
  std::vector<Symbol> chainAlphabet = {};
  for (unsigned i = 0; i < divided_line.size(); i++) {
    chainAlphabet.push_back(Symbol(divided_line[i]));
  }

  // Creamos la cadena
  if (chainAlphabet.empty())
    *this = Chain(chainSymbols);
  else
    *this = Chain(chainSymbols, new Alphabet(chainAlphabet));

}

// Comprueba si la cadena está formada por símbolos del mismo alfabeto
bool
Chain::checkChain() {
  bool check = true;
  for (unsigned i = 0; i < symbols_.size(); i++) {
    for (unsigned j = 0; j < alphabet_->getSymbols().size(); j++)
      if (symbols_[i] == alphabet_->getSymbols()[j]) {
        check = true;
        break;
      } else {
        check = false;
      }
    if (!check) return false;
    }
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

// Convierte una string separada por espacios en un vector
std::vector<std::string>
stringToVector(std::string my_string) {
  std::vector<std::string> my_vector = {""};
  unsigned j = 0;
  for (unsigned i = 0; i < my_string.size(); i++) {
    if (my_string[i] != ' ') {
      my_vector[j] += my_string[i];
    } else {
      j++;
      my_vector.resize(j + 1);
    }
  }
  return my_vector;
}

template <class T>
bool
include(std::vector<T> v, T element) {
  for(unsigned i = 0; i < v.size(); i++)
    if (v[i] == element)
      return true;
  return false;
}