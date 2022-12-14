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
* a la representación de un símbolo.
*/

#pragma once

#include <iostream>

const std::string kEmptyChainSymbol = "&";

class Symbol {

  public:
    // Constructor & Destructor
    Symbol(std::string);
    Symbol();
    ~Symbol();
  
    // Getters & Setters
    std::string getSymbol();
    void setSymbol(std::string);

    // Sobrecarga de operadores
    bool operator==(const Symbol&) const;
    bool operator!=(const Symbol&) const;
    Symbol& operator=(Symbol);
    bool operator<(const Symbol&) const;

    // E/S
    void write(std::ostream& = std::cout);
    void read(std::istream& = std::cin);
  
  private:
    std::string symbol_;
};

// Operadores sobrecargados de E/S
std::ostream& operator<<(std::ostream&, Symbol&);
std::istream& operator>>(std::istream&, Symbol&);

// Comprueba si una cadena es subcadena de otra
bool isSubstring(std::string, std::string);