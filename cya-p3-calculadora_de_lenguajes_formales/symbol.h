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
* a la representación de un símbolo.
*/

#pragma once

#include <iostream>

class Symbol {

  public:
    // Constructor & Destructor
    Symbol(std::string);
    ~Symbol();
  
    // Getters & Setters
    std::string getSymbol();
    void setSymbol(std::string);

    // Sobrecarga de operadores
    bool operator==(const Symbol&);
    bool operator<(const Symbol&) const;
    Symbol& operator=(Symbol);

    // E/S
    void write(std::ostream& = std::cout);
    void read(std::istream& = std::cin);
  
  private:
    std::string symbol_;
};

// Operadores sobrecargados de E/S
std::ostream& operator<<(std::ostream&, Symbol&);
std::istream& operator>>(std::istream&, Symbol&);