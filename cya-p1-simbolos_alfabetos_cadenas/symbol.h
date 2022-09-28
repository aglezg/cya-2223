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
  
  private:
    std::string symbol_;
};