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