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
* Este archivo ...
*/

#pragma once

#include <iostream>
#include <set>

#include "symbol.h"

class Alphabet {

  public:
    Alphabet(std::set<Symbol>);
    ~Alphabet();
  
    std::set<Symbol> getSymbols();
    void setSymbols(std::set<Symbol>);

    bool addSymbol(Symbol);
    bool removeSymbol(Symbol);
    bool checkSymbol(Symbol);
  
  private:
    std::set<Symbol> symbols_;
};