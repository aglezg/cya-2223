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
Language::Language(std::set<Chain> chains) {
  chains_ = chains;
  // assert(checkear cada cadena pertenece al mismo alfabeto)
}

// Destructor
Language::~Language() {
  chains_.clear();
}
