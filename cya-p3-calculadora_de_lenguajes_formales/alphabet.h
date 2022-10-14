/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #01: Símbolos, alfabetos y cadenas
* @author Adrián González Galván
* @date 13/10/2022
*
* Este archivo contiene la implementación de una clase correspondiente
* a la representación de un alfabeto.
*/

#pragma once

#include <iostream>
#include <set>
#include <algorithm>

#include "symbol.h"

class Alphabet {

  public:
    // Constructor & Destructor
    Alphabet(std::set<Symbol>);
    ~Alphabet();
  
    // Getters & Setters
    std::set<Symbol> getSymbols();
    void setSymbols(std::set<Symbol>);

    // Operaciones
    bool addSymbol(Symbol);
    bool removeSymbol(Symbol);
    bool checkSymbol(Symbol);

    // Impresión por pantalla
    void print();

    // E/S
    void write(std::ostream& = std::cout);

    // Operadores sobrecargados
    bool operator==(Alphabet&);
  
  private:
    std::set<Symbol> symbols_;
    void removeDuplicates();
};

// Operadores sobrecargados de E/S
std::ostream& operator<<(std::ostream&, Alphabet&);