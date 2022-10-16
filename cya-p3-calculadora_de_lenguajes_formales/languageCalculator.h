/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #03: Calculadora de lenguajes formales
* @author Adrián González Galván
* @date 20/10/2022
*
* Este archivo contiene la implementación de una clase correspondiente
* a la representación de una calculadora de operaciones con lenguajes.
*/

#pragma once

#include <iostream>
#include "language.h"

#define kOpenningSet = '{';
#define kClosingSet = '}';
#define kChainSeparator = ',';


class LanguageCalculator {
  public:
    // Constructor & Destructor
    LanguageCalculator(std::vector<Language>, std::vector<std::string>, std::vector<std::string>);
    LanguageCalculator();
    ~LanguageCalculator();

    // Getters & Setters
    std::vector<Language> getLanguages();
    std::vector<std::string> getLanguageNames();
    std::vector<std::string> getOperations();

    // Impresión por pantalla
    void print();

    // Lectura
    void read(std::istream& = std::cin);

  private:
    std::vector<Language> languages_;
    std::vector<std::string> languageNames_;
    std::vector<std::string> operations_;
};