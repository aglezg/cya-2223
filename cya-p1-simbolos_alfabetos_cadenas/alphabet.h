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
* Este archivo contiene la implementación de una clase correspondiente
* a la representación de un alfabeto.
*/

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "symbol.h"

class Alphabet {

  public:
    // Constructor & Destructor
    Alphabet(std::vector<Symbol>);
    ~Alphabet();
  
    // Getters & Setters
    std::vector<Symbol> getSymbols();
    void setSymbols(std::vector<Symbol>);

    // Operaciones
    bool addSymbol(Symbol);
    bool removeSymbol(Symbol);
    bool checkSymbol(Symbol);

    // Impresión por pantalla
    void print();

    // E/S
    void write(std::ostream& = std::cout);
  
  private:
    std::vector<Symbol> symbols_;
    void removeDuplicates();
};

// Operadores sobrecargados de E/S
std::ostream& operator<<(std::ostream&, Alphabet&);