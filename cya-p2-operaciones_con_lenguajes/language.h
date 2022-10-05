/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #02: Operaciones con lenguajes
* @author Adrián González Galván
* @date 13/10/2022
*
* Este archivo contiene la implementación de una clase correspondiente
* a la representación de un símbolo.
*/

#pragma once

#include <iostream>
#include <set>

#include "chain.h"

class Language {

  public:
    // Constructor & Destructor
    Language(std::set<Chain> = {});
    ~Language();
  
    // Getters & Setters
    std::set<Chain> getChains();
    void setChains(std::set<Chain> = {});

    // Impresión por pantalla
    void print();

    // Sobrecarga de operadores

    // E/S
    void write(std::ostream& = std::cout);
    void read(std::istream& = std::cin);
  
  private:
    std::set<Chain> chains_;
    bool checkChains();
};

// Operadores sobrecargados de E/S
std::ostream& operator<<(std::ostream&, Language&);
std::istream& operator>>(std::istream&, Language&);