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

class Symbol {

  public:
    Symbol(std::string);
    ~Symbol();
  
    std::string getSymbol();
    void setSymbol(std::string);

    bool operator==(Symbol&);
    Symbol& operator=(Symbol);

    // E/S
    void write(std::ostream& os = std::cout);
  
  private:
    std::string symbol_;
};

// Operadores sobrecargados de E/S
std::ostream& operator<<(std::ostream& os, Symbol& symbol);