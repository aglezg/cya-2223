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
* a la representación de una cadena.
*/

#pragma once

#include <iostream>

#include <iostream>
#include <vector>
#include "alphabet.h"

const char kEmptyChain = '&';

class Chain {
  public:
    // Constructor & Destructor
    Chain(std::vector<Symbol>);
    ~Chain();

    // Getters
    std::vector<Symbol> getSymbols();

    // Setters
    void setSymbols(std::vector<Symbol>);

    // Impresión por pantalla
    void print();

    // Operaciones
    unsigned length();
    Chain inverse();
    std::vector<Chain> prefixes();
    std::vector<Chain> suffixes();
    std::vector<Chain> substrings();
    Chain concat(Chain);
    bool isPalindrome();

    // Sobrecarga de operadores
    bool operator==(Chain&);
    bool operator<(const Chain&) const;

    // E/S
    void write(std::ostream&);
    void read(std::istream&);

  private:
    std::vector<Symbol> symbols_;
};

// Comprueba si una determinada cadena está formada con símbolos de un
// determinado alfabeto
bool checkChain(Alphabet*, Chain);

// Operaciones sobrecargados de E/S
std::istream& operator>>(std::istream&, Chain&);
std::ostream& operator<<(std::ostream&, Chain&);

// Comprueba si un determinado elemento pertenece a un vector
template <class T>
bool include(std::vector<T>, T);

// Conversión de string a vector
std::vector<std::string> stringToVector(std::string);