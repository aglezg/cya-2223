/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #08: Gramáticas en forma normal de Chomsky
* @author Adrián González Galván
* @date 24/11/2022
*
* Este archivo contiene la implementación de una clase correspondiente
* a la representación de una producción de una producción.
*/

#pragma once

#include <iostream>
#include <vector>
#include "symbol.h"

class Production {
  public:
    // Constructor && Destructor
    Production(Symbol, std::vector<Symbol> = {});
    Production();
    ~Production();

    // Getters
    Symbol getStart();
    std::vector<Symbol> getGeneration();

    // Setters
    void setStart(Symbol);
    void setGeneration(std::vector<Symbol>);

    // Operaciones
    bool isEmpty();

    // print
    void print();

    // Sobrecarga de operadores
    bool operator<(const Production&) const;
    bool operator==(const Production&) const;
    bool operator!=(const Production&) const;

    // E/S
    void write(std::ostream& = std::cout);

  private:
  Symbol start_;
  std::vector<Symbol> generation_;
};

// Sobrecarga de los operadores de E/S
std::ostream& operator<<(std::ostream&, Production&);