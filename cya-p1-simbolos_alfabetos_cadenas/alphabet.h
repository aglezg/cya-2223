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
#include <vector>
#include <algorithm>

#include "symbol.h"

class Alphabet {

  public:
    Alphabet(std::vector<Symbol>);
    ~Alphabet();
  
    std::vector<Symbol> getSymbols();
    void setSymbols(std::vector<Symbol>);

    bool addSymbol(Symbol);
    bool removeSymbol(Symbol);
    int checkSymbol(Symbol);

    void print();
  
  private:
    std::vector<Symbol> symbols_;
    void removeDuplicates();
};