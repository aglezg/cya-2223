/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #01: Símbolos, alfabetos y cadenas
* @author Adrián González Galván
* @date 06/10/2022
*
* Este archivo contiene el desarrollo de los métodos de la clase Chain.
*/

#include "chain.h"
#include <cassert>

// Constructor sin especificar alfabeto
Chain::Chain(std::vector<Symbol> symbols) {
  symbols_ = symbols;
};


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
std::vector<Chain>
Chain::prefixes() {
  std::vector<Chain> chainPrefixes = {Chain({})};
  std::vector<Symbol> symbolsCopy; 
  for (unsigned i = 0; i < this->length(); i++) {
    symbolsCopy.push_back(getSymbols()[i]);
    chainPrefixes.push_back(Chain(symbolsCopy));
  }
  return chainPrefixes;
}

// Calcula las cadenas sufijos de la misma cadena
std::vector<Chain>
Chain::suffixes() {
  std::vector<Chain> chainSuffixes = {};
  std::vector<Symbol> symbolsCopy = getSymbols(); 
  for (int i = this->length() - 1; i >= 0; i--) {
    chainSuffixes.push_back(Chain(symbolsCopy));
    symbolsCopy.erase(symbolsCopy.begin());
  }
  chainSuffixes.push_back(Chain({}));
  return chainSuffixes;
}


// Calcula las subcadenas de la misma cadena
std::vector<Chain>
Chain::substrings() {
  std::vector<Chain> chainSubstrings = {Chain(std::vector<Symbol>({}))};
  
  int substrings_size = 1;
  while (substrings_size <= length()) {
    for (unsigned i = 0; i <= length() - substrings_size; i++) {
      std::vector<Symbol> symbolsCopy = {};
      for (unsigned j = i; j < i + substrings_size; j++)
        symbolsCopy.push_back(getSymbols()[j]);
      if (!include(chainSubstrings, Chain(symbolsCopy)))
        chainSubstrings.push_back(Chain(symbolsCopy));
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
    std::cout << kEmptyChainPrint << std::endl;
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

// Sobrecarga del operador "<"
bool Chain::operator<(const Chain& chain) const {
  return symbols_ < chain.symbols_;
}

// Escritura
void
Chain::write(std::ostream& os) {
  if (getSymbols().empty())
    os << kEmptyChainPrint;
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

  // Extraemos el alfabeto
  std::vector<Symbol> chainAlphabet = {};
  for (unsigned i = 0; i < divided_line.size(); i++) {
    chainAlphabet.push_back(Symbol(divided_line[i]));
  }

  // Definimos vector de simbolos (cadena)
  std::vector<Symbol> chainSymbols= {};

  if (chainAlphabet.empty()) { // Alfabeto vacío
    for (unsigned i = 0; i < chainSymbolsString.size(); i++) {
      std::string str;
      str += chainSymbolsString[i];
      chainSymbols.push_back(Symbol(str));
    }
    *this = Chain(chainSymbols);
  } else { // Alfabeto no vacío
    Alphabet* myAlphabet = new Alphabet(std::set<Symbol>(chainAlphabet.begin(), chainAlphabet.end()));
    std::string str;
    for (unsigned i = 0; i < chainSymbolsString.size(); i++) {
      str += chainSymbolsString[i];
      if (myAlphabet->checkSymbol(Symbol(str))) {
        chainSymbols.push_back(Symbol(str));
        str = "";
      }
    }
    if (str != "")
      chainSymbols.push_back(Symbol(str));
    *this = Chain(chainSymbols);
  }

}

// Comprueba si una cadena está formada por símbolos de un alfabeto
bool
checkChain(Alphabet* alphabet, Chain chain) {
  for (unsigned i = 0; i < chain.length(); i++)
    if (!alphabet->checkSymbol(chain.getSymbols()[i]))
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

// Comprueba si un elemento pertenece a un determinado vector
template <class T>
bool
include(std::vector<T> v, T element) {
  for(unsigned i = 0; i < v.size(); i++)
    if (v[i] == element)
      return true;
  return false;
}